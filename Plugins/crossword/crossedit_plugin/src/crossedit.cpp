/*
 * Copyright (C) 2012 Kulabuhov Michael, Kemerovo, Russia.
 *
 * See the LICENSE file for terms of use.
 */

#include "crossedit.h"

const int min_size = 10;

Crossedit::Crossedit(QObject *parent, ICross *cross) :
  QObject(parent),
  cross_(cross),
  width_(min_size),
  height_(min_size),
  words_(),
  editing_word_(nullptr),
  editing_word_index_(-1)
{
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
  IWord *word = nullptr;
  QObject *word_obj = nullptr;
  for (auto wrd_obj : words_)
  {
    IWord *wrd = qobject_cast<IWord*>(wrd_obj);
    if (!wrd) continue;
    if (wrd->direction()
        ? cell->x() == wrd->x() && cell->y() >= wrd->y() && cell->y() < wrd->y() + wrd->length()
        : cell->y() == wrd->y() && cell->x() >= wrd->x() && cell->x() < wrd->x() + wrd->length())
    {
      word = wrd;
      word_obj = wrd_obj;
      break;
    }
  }
  if (!word)
  {
    removeEmptyWords();
    word = cross_->createWord(this);
    word->setX(cell->x());
    word->setY(cell->y());
    word_obj = word->toObject();
    words_.append(word_obj);
    cell->setType(2);
    fillGrid();
    emit updateWords();
  }
  highlightWord(word_obj);
}

void Crossedit::editWord(QObject *word_obj, QString text)
{
  IWord *word = qobject_cast<IWord*>(word_obj);
  if (!word) return;
  word->setWord(text.toUpper());
  fillGrid();
  highlightWord(word_obj);
}

void Crossedit::rotateWord()
{
  if (!editing_word_) return;
  editing_word_->setDirection(!editing_word_->direction());
  fillGrid();
  highlightWord(words_.at(editing_word_index_));
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
        cell->setLetter(word->word().at(i));
      else
        cell->setLetter("?");
    }
  }
  grid_->paintGrid(words_);
}
