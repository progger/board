/*
 * Copyright (C) 2013 Kulabuhov Michael, Kemerovo, Russia.
 *
 * See the LICENSE file for terms of use.
 */

#include "paintutils.h"
#include "rectangle.h"
#include "rectanglegen.h"

RectangleGen::RectangleGen(ISheetCanvas *canvas) :
  ShapeGen(canvas)
{
}

void RectangleGen::begin(const QPointF &p)
{
  ShapeGen::begin(p);
  _item = createItem<Rectangle>(_canvas, p);
}
