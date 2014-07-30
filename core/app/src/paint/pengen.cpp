/*
 * Copyright (C) 2013 Michael Kulabuhov, Kemerovo, Russia.
 *
 * See the LICENSE file for terms of use.
 */

#include "paintutils.h"
#include "pen.h"
#include "pengen.h"

PenGen::PenGen(ISheetCanvas *canvas) :
  ShapeGen(canvas)
{
}

void PenGen::begin(const QPointF &p)
{
  ShapeGen::begin(p);
  Pen *pen = createItem<Pen>(_canvas, p);
  pen->points().append(QPointF(0, 0));
  _item = pen;
}

void PenGen::end(const QPointF &)
{
  //move(p);  //TODO: Почему-то это приводит к глюку на винде (полосы влево вверх)
  Pen *pen = static_cast<Pen*>(_item);
  pen->points().squeeze();
  pen->savePoints();
  _canvas->pushState();
  _canvas->updateSheetRect();
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
  pen->points().append(QPointF(dx, dy));
  QSizeF size(width, height);
  pen->setSize(size);
  pen->setInnerSize(size);
  _item->update();
}
