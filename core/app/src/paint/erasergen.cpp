/*
 * Copyright (C) 2014 Michael Kulabuhov, Kemerovo, Russia.
 *
 * See the LICENSE file for terms of use.
 */

#include "commonshape.h"
#include "global.h"
#include "erasergen.h"

EraserGen::EraserGen(ISheetCanvas *canvas) :
  ShapeGen(canvas)
{
}

void EraserGen::begin(const QPointF &p)
{
  ShapeGen::begin(p);
  move(p);
}

void EraserGen::end(const QPointF &p)
{
  move(p);
  _canvas->pushState();
  _canvas->updateSheetRect();
}

void EraserGen::move(const QPointF &p)
{
  float es = g_core->paint()->eraserSize();
  QSizeF size(es * 2, es * 2);
  QRectF beg(QPointF(_start.x() - es, _start.y() - es), size);
  QRectF end(QPointF(p.x() - es, p.y() - es), size);
  for (QQuickItem *item : _canvas->container()->childItems())
  {
    CommonShape *shape = qobject_cast<CommonShape*>(item);
    if (shape)
    {
      shape->erase(beg, end);
    }
  }
  _start = p;
}
