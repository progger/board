/*
 * Copyright (C) 2012 Kulabuhov Michael, Kemerovo, Russia.
 *
 * See the LICENSE file for terms of use.
 */

#include "row.h"

Row::Row(QObject *parent) :
  QObject(parent),
  cells_()
{
}

void Row::addCell(QObject *cell)
{
  cells_.append(cell);
}
