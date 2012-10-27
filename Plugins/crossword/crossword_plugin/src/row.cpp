/*
 * Copyright (C) 2012 Kulabuhov Michael, Kemerovo, Russia.
 *
 * See the LICENSE file for terms of use.
 */

#include "cell.h"
#include "row.h"

Row::Row(QObject *parent) :
  QObject(parent),
  cells_()
{
}

void Row::fill(int y, int width)
{
  cells_.clear();
  for (int x = 0; x < width; x++)
  {
    auto cell = new Cell(x, y, this);
    cells_.append(cell);
  }
}

void Row::hideHighlight()
{
  for (auto cell_obj : cells_)
  {
    Cell *cell = qobject_cast<Cell*>(cell_obj);
    cell->setHighlight(false);
    cell->setEditing(false);
  }
}
