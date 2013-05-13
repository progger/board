/*
 * Copyright (C) 2013 Kulabuhov Michael, Kemerovo, Russia.
 *
 * See the LICENSE file for terms of use.
 */

#include "sheetcanvas.h"
#include "paint.h"
#include "shape.h"
#include "shapegen.h"

ShapeGen::ShapeGen(SheetCanvas *canvas) :
  _canvas(canvas)
{
}

Paint *ShapeGen::paint() const
{
  return _canvas->paint();
}

void ShapeGen::begin(const QPointF &p)
{
  _start = p;
}

void ShapeGen::end(const QPointF &p)
{
  move(p);
  _item = nullptr;
  _canvas->updateSheetRect();
}

void ShapeGen::move(const QPointF &p)
{
  if (!_item) return;
  qreal x1 = qMin(_start.x(), p.x());
  qreal y1 = qMin(_start.y(), p.y());
  qreal x2 = qMax(_start.x(), p.x());
  qreal y2 = qMax(_start.y(), p.y());
  _item->setPosition(QPointF(x1, y1));
  QSizeF size(x2 - x1, y2 - y1);
  _item->setSize(size);
  _item->setInnerSize(size);
  _item->update();
}
