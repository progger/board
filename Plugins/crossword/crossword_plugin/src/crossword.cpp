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
  QString data(file.readAll());
  Parser parser(data);
  QString str;
  if (!parser.read(str) || str !="<ACROSS PUZZLE>") return false;
  if (!parser.readTo("<SIZE>")) return false;
  if (!parser.read(str)) return false;
  auto size_parts = str.split('x');
  bool ok;
  width_ = size_parts[0].toInt(&ok);
  if (!ok) return false;
  height_ = size_parts[1].toInt(&ok);
  if (!ok) return false;
  if (!parser.readTo("<GRID>")) return false;
  QChar grid[height_][width_];
  for (int y = 0; y < height_; y++)
  {
    if (!parser.read(str) || str.length() != width_) return false;
    str = str.toUpper();
    memcpy(grid[y], str.data(), width_ * sizeof(QChar));
  }
  if (!parser.readTo("<ACROSS>")) return false;
  for (int y = 0; y < height_; y++)
  {
    QString wrd = "";
    for (int x = 0; x < width_; x++)
    {
      QChar chr = grid[y][x];
      if (chr == '.')
      {
        if (wrd.length() > 1)
        {
          if (!parser.read(str)) return false;
          words_.append(new Word(x - wrd.length(), y, false, wrd, str, this));
          wrd = "";
        }
      }
      else
      {
        wrd.append(chr);
      }
    }
    if (wrd.length() > 1)
    {
      if (!parser.read(str)) return false;
      words_.append(new Word(width_ - wrd.length(), y, false, wrd, str, this));
    }
  }
  if (!parser.readTo("<DOWN>")) return false;
  for (int y = 0; y < height_ - 1; y++)
  {
    for (int x = 0; x < width_; x++)
    {
      QChar chr = grid[y][x];
      if (chr != '.')
      {
        if (y == 0 || grid[y-1][x] == '.')
        {
          QString wrd = chr;
          for (int i = y + 1; i < height_; i++)
          {
            chr = grid[i][x];
            if (chr != '.')
            {
              wrd.append(chr);
            }
            else
            {
              break;
            }
          }
          if (wrd.length() > 1)
          {
            if (!parser.read(str)) return false;
            words_.append(new Word(x, y, true, wrd, str, this));
          }
        }
      }
    }
  }

  bool change;
  do
  {
    change = false;
    for (int y = 0; y < height_; y++)
    {
      for (int x = 0; x < width_; x++)
      {
        if (grid[y][x] == '.' && (
              x == 0 || x == width_ - 1 || y == 0 || y == width_ -1 ||
              grid[y][x - 1] == ' ' || grid[y][x + 1] == ' ' ||
              grid[y - 1][x] == ' ' || grid[y + 1][x] == ' '))
        {
          grid[y][x] = ' ';
          change = true;
        }
      }
    }
  }
  while (change);

  grid_->fill(width_, height_);
  for (int y = 0; y < height_; y++)
  {
    for (int x = 0; x < width_; x++)
    {
      QChar chr = grid[y][x];
      auto cell = grid_->getCell(x, y);
      cell->setType(chr == ' ' ? 0 : chr == '.' ? 1 : 2);
    }
  }
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
