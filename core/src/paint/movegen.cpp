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
  QPointF dp = p - _start;
  for (QQuickItem *item : _canvas->container()->childItems())
  {
    item->setPosition(item->position() + dp);
  }
  _start = p;
}
