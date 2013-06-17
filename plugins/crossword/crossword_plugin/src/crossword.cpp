/*
 * Copyright (C) 2012 Michael Kulabuhov, Kemerovo, Russia.
 *
 * See the LICENSE file for terms of use.
 */

#include <QFile>
#include "iparser.h"
#include "icell.h"
#include "crossword.h"

Crossword::Crossword(QObject *parent, ICross *cross) :
  QObject(parent),
  cross_(cross),
  width_(0),
  height_(0),
  words_(),
  editing_word_(nullptr),
  editing_word_index_(-1),
  editing_pos_(0)
{
  grid_ = cross_->createGrid(this);
}

bool Crossword::init(const QString &file_name)
{
  auto parser = cross_->createParser(this, &words_);
  {
    QFile file(file_name);
    if (!file.open(QIODevice::ReadOnly)) goto error;
    if (!parser->parse(&file)) goto error;
    grid_->fill(parser->width(), parser->height());
    grid_->paintGrid(words_);
    delete parser;
    return true;
  }
error:
  delete parser;
  return false;
}

void Crossword::hideHighlight()
{
  grid_->hideHighlight();
  for (auto word_obj : words_)
  {
    IWord *word = qobject_cast<IWord*>(word_obj);
    if (!word) continue;
    word->setHighlight(false);
  }
  editing_word_ = nullptr;
  editing_word_index_ = -1;
  editing_pos_ = 0;
  emit updateEditingWord();
}

void Crossword::highlightWord(QObject *word_obj)
{
  IWord *word = qobject_cast<IWord*>(word_obj);
  if (!word || word->accepted()) return;
  hideHighlight();
  word->setHighlight(true);
  for (int i = 0; i < word->length(); i++)
  {
    int x = word->x() + (word->direction() ? 0 : i);
    int y = word->y() + (word->direction() ? i : 0);
    auto cell = grid_->getCell(x, y);
    cell->setHighlight(true);
  }
  editing_word_ = word;
  editing_word_index_ = words_.indexOf(word_obj);
  editing_pos_ = 0;
  setEditing();
  emit updateEditingWord();
}

void Crossword::highlightCell(QObject *cell_obj)
{
  ICell *cell = qobject_cast<ICell*>(cell_obj);
  if (!cell || cell->type() != 2) return;
  for (auto word_obj : words_)
  {
    IWord *word = qobject_cast<IWord*>(word_obj);
    if (!word) continue;
    if (word->direction()
        ? cell->x() == word->x() && cell->y() >= word->y() && cell->y() < word->y() + word->length()
        : cell->y() == word->y() && cell->x() >= word->x() && cell->x() < word->x() + word->length())
    {
      highlightWord(word_obj);
      break;
    }
  }
}

void Crossword::edit(QString key)
{
  if (key.isEmpty() || !editing_word_) return;
  key = key.toUpper();
  bool direction = editing_word_->direction();
  int x = editing_word_->x() + (direction ? 0 : editing_pos_);
  int y = editing_word_->y() + (direction ? editing_pos_ : 0);
  auto cell = grid_->getCell(x, y);
  cell->setLetter(key);
  cell->setEditing(false);
  editing_pos_++;
  setEditing();
}

void Crossword::setEditing()
{
  bool direction = editing_word_->direction();
  int length = editing_word_->length();
  int x = editing_word_->x() + (direction ? 0 : editing_pos_);
  int y = editing_word_->y() + (direction ? editing_pos_ : 0);
  auto cell = grid_->getCell(x, y);
  while (cell->accepted() && editing_pos_ < length)
  {
    editing_pos_++;
    if (direction)
      y++;
    else
      x++;
    cell = grid_->getCell(x, y);
  }
  if (editing_pos_ >= length)
  {
    checkWord();
    hideHighlight();
  }
  else
  {
    cell->setEditing(true);
  }
}

void Crossword::checkWord()
{
  int count = editing_word_->length();
  for (int i = 0; i < count; i++)
  {
    int x = editing_word_->x() + (editing_word_->direction() ? 0 : i);
    int y = editing_word_->y() + (editing_word_->direction() ? i : 0);
    auto cell = grid_->getCell(x, y);
    if (cell->letter().length() != 1 || cell->letter().at(0) != editing_word_->word().at(i)) return;
  }
  editing_word_->setAccepted(true);
  for (int i = 0; i < count; i++)
  {
    int x = editing_word_->x() + (editing_word_->direction() ? 0 : i);
    int y = editing_word_->y() + (editing_word_->direction() ? i : 0);
    auto cell = grid_->getCell(x, y);
    cell->setAccepted(true);
  }
}
