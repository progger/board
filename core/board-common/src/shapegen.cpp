/*
 * Copyright (C) 2013 Michael Kulabuhov, Kemerovo, Russia.
 *
 * See the LICENSE file for terms of use.
 */

#include "shape.h"
#include "shapegen.h"

ShapeGen::ShapeGen(ISheetCanvas *canvas) :
  _start(),
  _canvas(canvas),
  _item(nullptr)
{
}

void ShapeGen::begin(const QPointF &p)
{
  _start = p;
}

void ShapeGen::end(const QPointF &p)
{
  move(p);
  _item = nullptr;
  _canvas->pushState();
  _canvas->updateSheetRect();
}

void ShapeGen::move(const QPointF &p)
{
  if (!_item) return;
  qreal x1 = std::min(_start.x(), p.x());
  qreal y1 = std::min(_start.y(), p.y());
  qreal x2 = std::max(_start.x(), p.x());
  qreal y2 = std::max(_start.y(), p.y());
  _item->setPosition(QPointF(x1, y1));
  QSizeF size(x2 - x1, y2 - y1);
  _item->setSize(size);
  _item->setInnerSize(size);
  _item->update();
}
