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
  rows_.clear();
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
