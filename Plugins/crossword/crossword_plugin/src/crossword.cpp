/*
 * Copyright (C) 2012 Kulabuhov Michael, Kemerovo, Russia.
 *
 * See the LICENSE file for terms of use.
 */

#include <QFile>
#include "parser.h"
#include "cell.h"
#include "crossword.h"

Crossword::Crossword(QObject *parent) :
  QObject(parent),
  width_(0),
  height_(0),
  words_(),
  editing_word_(nullptr),
  editing_pos_(0)
{
  grid_ = new Grid(this);
}

bool Crossword::init(const QString &file_name)
{
  QFile file(file_name);
  if (!file.open(QIODevice::ReadOnly)) return false;
  QTextStream stream(&file);
  Parser parser(this, &words_);
  if (!parser.parse(&stream)) return false;
  grid_->fill(parser.width(), parser.height());
  for (auto word_obj : words_)
  {
    Word *word = qobject_cast<Word*>(word_obj);
    int x = word->x();
    int y = word->y();
    bool direction = word->direction();
    int length = word->length();
    for (int i = 0; i < length; i++)
    {
      auto cell = grid_->getCell(x, y);
      cell->setType(2);
      if (direction) y++;
      else x++;
    }
  }
  grid_->paintGrid();
  return true;
}

void Crossword::hideHighlight()
{
  grid_->hideHighlight();
  for (auto word_obj : words_)
  {
    Word *word = qobject_cast<Word*>(word_obj);
    word->setHighlight(false);
  }
  editing_word_ = nullptr;
  editing_pos_ = 0;
}

void Crossword::highlightWord(QObject *word_obj)
{
  Word *word = qobject_cast<Word*>(word_obj);
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
  editing_pos_ = 0;
  auto cell = grid_->getCell(word->x(), word->y());
  cell->setEditing(true);
}

void Crossword::highlightCell(QObject *cell_obj)
{
  Cell *cell = qobject_cast<Cell*>(cell_obj);
  if (!cell || cell->type() != 2) return;
  for (auto word_obj : words_)
  {
    Word *word = static_cast<Word*>(word_obj);
    if (word->direction()
        ? cell->x() == word->x() && cell->y() >= word->y() && cell->y() < word->y() + word->length()
        : cell->y() == word->y() && cell->x() >= word->x() && cell->x() < word->x() + word->length())
    {
      highlightWord(word);
      break;
    }
  }
}

void Crossword::edit(QString key)
{
  if (key.isEmpty() || !editing_word_) return;
  key = key.toUpper();
  bool direction = editing_word_->direction();
  int length = editing_word_->length();
  int x = editing_word_->x() + (direction ? 0 : editing_pos_);
  int y = editing_word_->y() + (direction ? editing_pos_ : 0);
  auto cell = grid_->getCell(x, y);
  cell->setLetter(key);
  cell->setEditing(false);
  editing_pos_++;
  while (editing_pos_ < length)
  {
    if (direction)
      y++;
    else
      x++;
    cell = grid_->getCell(x, y);
    if (!cell->accepted()) break;
    editing_pos_++;
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
