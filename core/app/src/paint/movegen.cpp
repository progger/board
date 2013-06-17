/*
 * Copyright (C) 2013 Michael Kulabuhov, Kemerovo, Russia.
 *
 * See the LICENSE file for terms of use.
 */

#include "sheetcanvas.h"
#include "movegen.h"

MoveGen::MoveGen(ISheetCanvas *canvas) :
  ShapeGen(canvas)
{
}

void MoveGen::move(const QPointF &p)
{
  QPointF dp = _start - p;
  SheetCanvas *canvas = static_cast<SheetCanvas*>(_canvas);
  canvas->moveSheet(dp.x(), dp.y());
  _start = p;
}

void MoveGen::end(const QPointF &p)
{
  move(p);
}
