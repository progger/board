/*
 * Copyright (C) 2012 Kulabuhov Michael, Kemerovo, Russia.
 *
 * See the LICENSE file for terms of use.
 */

#include <QFile>
#include "crossedit.h"

const int min_size = 10;

Crossedit::Crossedit(QObject *parent, ICore *core, ICross *cross) :
  QObject(parent),
  core_(core),
  cross_(cross),
  width_(min_size),
  height_(min_size),
  words_(),
  editing_word_(nullptr),
  editing_word_index_(-1),
  cross_name_()
{
  parser_ = cross->createParser(this, &words_);
  grid_ = cross->createGrid(this);
  grid_->fill(width_, height_);
}

void Crossedit::hideHighlight()
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
  emit updateEditingWord();
}

void Crossedit::highlightWord(QObject *word_obj)
{
  IWord *word = qobject_cast<IWord*>(word_obj);
  if (!word) return;
  if (word != editing_word_)
  {
    hideHighlight();
    word->setHighlight(true);
    editing_word_ = word;
    editing_word_index_ = words_.indexOf(word_obj);
    emit updateEditingWord();
  }
  int length = word->length();
  if (!length) length = 1;
  for (int i = 0; i < length; i++)
  {
    int x = word->x() + (word->direction() ? 0 : i);
    int y = word->y() + (word->direction() ? i : 0);
    auto cell = grid_->getCell(x, y);
    cell->setHighlight(true);
  }
}

void Crossedit::highlightCell(QObject *cell_obj)
{
  ICell *cell = qobject_cast<ICell*>(cell_obj);
  if (!cell) return;
  IWord *word_h = nullptr;
  IWord *word_v = nullptr;
  for (auto word_obj : words_)
  {
    IWord *word = qobject_cast<IWord*>(word_obj);
    if (!word) continue;
    if (word->direction()
        ? cell->x() == word->x() && cell->y() >= word->y() && cell->y() < word->y() + word->length()
        : cell->y() == word->y() && cell->x() >= word->x() && cell->x() < word->x() + word->length())
    {
      if (word->direction())
      {
        if (!word_v)
          word_v = word;
      }
      else
      {
        if (!word_h)
          word_h = word;
      }
    }
  }
  if (!word_h || !word_v)
  {
    removeEmptyWords();
    auto word = cross_->createWord(this);
    word->setX(cell->x());
    word->setY(cell->y());
    if (!word_h)
    {
      word->setDirection(false);
      word_h = word;
    }
    else
    {
      word->setDirection(true);
      word_v = word;
    }
    words_.append(word->toObject());
    fillGrid();
    emit updateWords();
  }
  if (!word_v)
    highlightWord(word_h->toObject());
  else
    if (word_h->highlight())
      highlightWord(word_v->toObject());
    else
      highlightWord(word_h->toObject());
}

void Crossedit::editWord(QObject *word_obj, QString text)
{
  IWord *word = qobject_cast<IWord*>(word_obj);
  if (!word) return;
  word->setWord(text.toUpper());
  fillGrid();
  highlightWord(word_obj);
}

void Crossedit::editCrossName(QString text)
{
  //TODO: Проверка на спецсимволы
  cross_name_ = text;
  emit updateCrossName();
}

void Crossedit::rotateWord()
{
  if (!editing_word_) return;
  editing_word_->setDirection(!editing_word_->direction());
  fillGrid();
  highlightWord(words_.at(editing_word_index_));
}

void Crossedit::save()
{
  normalize();
  auto dir = core_->rootDir();
  dir.cd("crossword");
  QString base_file_name = dir.filePath(cross_name_);
  QFile file_txt(base_file_name + ".txt");
  QFile file_svg(base_file_name + ".svg");
  if (!file_txt.open(QIODevice::WriteOnly))
  {
    core_->showError(file_txt.errorString());
    return;
  }
  if (!file_svg.open(QIODevice::WriteOnly))
  {
    core_->showError(file_svg.errorString());
    return;
  }
  parser_->save(&file_txt, &file_svg);
}

void Crossedit::removeEmptyWords()
{
  auto iter = words_.begin();
  auto end = words_.end();
  while (iter != end)
  {
    QObject *word_obj = *iter;
    IWord *word = qobject_cast<IWord*>(word_obj);
    if (!word || !word->length())
    {
      word_obj->deleteLater();
      auto iter2 = words_.erase(iter);
      if (iter2 == iter)  //WTF? List.erase bug?
        iter++;
      else
        iter = iter2;
    }
    else
    {
      iter++;
    }
  }
}

void Crossedit::fillGrid()
{
  width_ = min_size;
  height_ = min_size;
  for (auto word_obj : words_)
  {
    IWord *word = qobject_cast<IWord*>(word_obj);
    if (!word) continue;
    int x = word->x() + (word->direction() ? 0 : word->length());
    int y = word->y() + (word->direction() ? word->length() : 0);
    if (width_ < x) width_ = x;
    if (height_ < y) height_ = y;
  }
  grid_->fill(width_, height_);
  for (auto word_obj : words_)
  {
    IWord *word = qobject_cast<IWord*>(word_obj);
    if (!word) continue;
    int length = word->length();
    for (int i = 0; i < length; i++)
    {
      int x = word->x() + (word->direction() ? 0 : i);
      int y = word->y() + (word->direction() ? i : 0);
      auto cell = grid_->getCell(x, y);
      if (cell->letter().isEmpty() || cell->letter() == word->word().at(i))
      {
        cell->setLetter(word->word().at(i));
      }
      else
      {
        cell->setLetter("?");
        cell->setError(true);
      }
    }
  }
  grid_->paintGrid(words_);
}

void Crossedit::normalize()
{
  removeEmptyWords();
  int min_x = width_;
  int min_y = height_;
  for (auto word_obj : words_)
  {
    IWord *word = qobject_cast<IWord*>(word_obj);
    if (word->x() < min_x) min_x = word->x();
    if (word->y() < min_y) min_y = word->y();
  }
  for (auto word_obj : words_)
  {
    IWord *word = qobject_cast<IWord*>(word_obj);
    word->setX(word->x() - min_x);
    word->setY(word->y() - min_y);
  }
  fillGrid();
  emit updateWords();
}
