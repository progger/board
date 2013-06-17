/*
 * Copyright (C) 2012 Michael Kulabuhov, Kemerovo, Russia.
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

Row::~Row()
{
  for (QObject *cell : cells_)
  {
    cell->deleteLater();
  }
}

void Row::fill(int y, int width)
{
  int x = cells_.length();
  int delta = width - x;
  while (delta > 0)
  {
    auto cell = new Cell(x++, y, this);
    cells_.append(cell);
    delta--;
  }
  while (delta < 0)
  {
    cells_.takeLast()->deleteLater();
    delta++;
  }
  for (auto cell_obj : cells_)
  {
    Cell *cell = qobject_cast<Cell*>(cell_obj);
    cell->setType(0);
    cell->setLetter(QString::null);
    cell->setHighlight(false);
    cell->setEditing(false);
    cell->setAccepted(false);
  }
  emit updateCells();
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
