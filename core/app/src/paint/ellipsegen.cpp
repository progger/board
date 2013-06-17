/*
 * Copyright (C) 2013 Michael Kulabuhov, Kemerovo, Russia.
 *
 * See the LICENSE file for terms of use.
 */

#include "sheetcanvas.h"
#include "paintutils.h"
#include "ellipse.h"
#include "ellipsegen.h"

EllipseGen::EllipseGen(ISheetCanvas *canvas) :
  ShapeGen(canvas)
{
}

void EllipseGen::begin(const QPointF &p)
{
  ShapeGen::begin(p);
  _item = createItem<Ellipse>(_canvas, p);
}
