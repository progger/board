/*
 * Copyright (C) 2012 Kulabuhov Michael, Kemerovo, Russia.
 *
 * See the LICENSE file for terms of use.
 */

#include "row.h"
#include "word.h"
#include "grid.h"

Grid::Grid(QObject *parent) :
  QObject(parent),
  rows_(),
  width_(0),
  height_(0)
{
}

void Grid::fill(int width, int height)
{
  int delta = height - rows_.length();
  while (delta > 0)
  {
    auto row = new Row(this);
    rows_.append(row);
    delta--;
  }
  while (delta < 0)
  {
    rows_.takeLast()->deleteLater();
    delta++;
  }
  int y = 0;
  for (auto row_obj : rows_)
  {
    Row *row = qobject_cast<Row*>(row_obj);
    if (!row) continue;
    row->fill(y++, width);
  }
  width_ = width;
  height_ = height;
  emit updateGrid();
}

Cell *Grid::getCell(int x, int y)
{
  Row *row = qobject_cast<Row*>(rows_.at(y));
  if (!row) return nullptr;
  return qobject_cast<Cell*>(row->cells().at(x));
}

QObject *Grid::toQObject()
{
  return this;
}

void Grid::hideHighlight()
{
  for (auto row_obj : rows_)
  {
    Row *row = qobject_cast<Row*>(row_obj);
    row->hideHighlight();
  }
}

void Grid::paintGrid(const QObjectList &words)
{
  qint8 grid[height_][width_];
  for (int y = 0; y < height_; y++)
  {
    for (int x = 0; x < width_; x++)
    {
      grid[y][x] = x > 0 && x < width_ - 1 && y > 0 && y < height_ - 1;
    }
  }

  for(auto word_obj : words)
  {
    Word *word = qobject_cast<Word*>(word_obj);
    int x = word->x();
    int y = word->y();
    bool direction = word->direction();
    int length = word->length();
    if (!length) length = 1;
    for (int i = 0; i < length; i++)
    {
      grid[y][x] = 2;
      if (direction) y++;
      else x++;
    }
  }

  while (true)
  {
    bool change = false;
    for (int y = 1; y < height_ - 1; y++)
    {
      for (int x = 1; x < width_ - 1; x++)
      {
        if (grid[y][x] == 1 && (grid[y - 1][x] == 0 || grid[y + 1][x] == 0 ||
                                grid[y][x - 1] == 0 || grid[y][x + 1] == 0))
        {
          grid[y][x] = 0;
          change = true;
        }
      }
    }
    if (!change) break;
  }
  for (int y = 0; y < height_; y++)
  {
    for (int x = 0; x < width_; x++)
    {
      auto cell = getCell(x, y);
      cell->setType(grid[y][x]);
    }
  }
}
