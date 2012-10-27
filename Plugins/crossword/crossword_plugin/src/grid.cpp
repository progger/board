/*
 * Copyright (C) 2012 Kulabuhov Michael, Kemerovo, Russia.
 *
 * See the LICENSE file for terms of use.
 */

#include "row.h"
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
  while (!rows_.empty()) delete rows_.takeFirst();
  for (int y = 0; y < height; y++)
  {
    auto row = new Row(this);
    row->fill(y, width);
    rows_.append(row);
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

void Grid::hideHighlight()
{
  for (auto row_obj : rows_)
  {
    Row *row = qobject_cast<Row*>(row_obj);
    row->hideHighlight();
  }
}

void Grid::paintGrid()
{
  qint8 grid[height_ + 2][width_ + 2];
  memset(grid, sizeof(grid), 0);
  for (int y = 0; y < height_; y++)
  {
    for (int x = 0; x < width_; x++)
    {
      auto cell = getCell(x, y);
      grid[y + 1][x + 1] = cell->type() == 2 ? 2 : 1;
    }
  }
  while (true)
  {
    bool change = false;
    for (int y = 1; y <= height_; y++)
    {
      for (int x = 1; x <= width_; x++)
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
      cell->setType(grid[y + 1][x + 1]);
    }
  }
}
