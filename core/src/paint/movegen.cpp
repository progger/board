/*
 * Copyright (C) 2013 Kulabuhov Michael, Kemerovo, Russia.
 *
 * See the LICENSE file for terms of use.
 */

#include "sheetcanvas.h"
#include "movegen.h"

MoveGen::MoveGen(SheetCanvas *canvas) :
  ShapeGen(canvas)
{
}

void MoveGen::move(const QPointF &p)
{
  QPointF dp = _start - p;
  _canvas->moveSheet(dp.x(), dp.y());
  _start = p;
}
