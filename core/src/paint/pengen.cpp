/*
 * Copyright (C) 2013 Kulabuhov Michael, Kemerovo, Russia.
 *
 * See the LICENSE file for terms of use.
 */

#include "sheetcanvas.h"
#include "paintutils.h"
#include "pen.h"
#include "pengen.h"

PenGen::PenGen(SheetCanvas *canvas) :
  ShapeGen(canvas)
{
}

void PenGen::begin(const QPointF &p)
{
  ShapeGen::begin(p);
  _item = createItem<Pen>(_canvas, p);
  Pen *pen = static_cast<Pen*>(_item);
  pen->points().push_back(QPointF(0, 0));
}

void PenGen::end(const QPointF &p)
{
  move(p);
  Pen *pen = static_cast<Pen*>(_item);
  pen->points().shrink_to_fit();
}

void PenGen::move(const QPointF &p)
{
  Pen *pen = static_cast<Pen*>(_item);
  qreal dx = p.x() - _start.x();
  qreal dy = p.y() - _start.y();
  qreal width = pen->width();
  qreal height = pen->height();
  if (dx < 0 || dy < 0)
  {
    qreal ddx = qMax(-dx, 0.0);
    qreal ddy = qMax(-dy, 0.0);
    for (QPointF &p : pen->points())
    {
      p.rx() += ddx;
      p.ry() += ddy;
      width = qMax(width, p.x());
      height = qMax(height, p.y());
    }
    dx += ddx;
    dy += ddy;
    _start.rx() -= ddx;
    _start.ry() -= ddy;
    pen->setPosition(_start);
  }
  width = qMax(width, dx);
  height = qMax(height, dy);
  pen->points().push_back(QPointF(dx, dy));
  QSizeF size(width, height);
  pen->setSize(size);
  pen->setInnerSize(size);
  _item->update();
}
