/*
 * Copyright (C) 2013 Kulabuhov Michael, Kemerovo, Russia.
 *
 * See the LICENSE file for terms of use.
 */

#include "sheetcanvas.h"
#include "paintutils.h"
#include "ellipse.h"
#include "circlegen.h"

CircleGen::CircleGen(SheetCanvas *canvas) :
  ShapeGen(canvas)
{
}

void CircleGen::begin(const QPointF &p)
{
  ShapeGen::begin(p);
  _item = createItem<Ellipse>(_canvas, p);
}

void CircleGen::move(const QPointF &p)
{
  qreal dx = p.x() - _start.x();
  qreal dy = p.y() - _start.y();
  qreal r = sqrt(dx * dx + dy * dy);
  _item->setPosition(QPointF(_start.x() - r, _start.y() - r));
  QSizeF size(r * 2, r * 2);
  _item->setSize(size);
  _item->setInnerSize(size);
  _item->update();
}
