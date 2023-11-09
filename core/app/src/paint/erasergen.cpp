/*
 * Copyright (C) 2014 Michael Kulabuhov, Kemerovo, Russia.
 *
 * See the LICENSE file for terms of use.
 */

#include <set>
#include "commonshape.h"
#include "global.h"
#include "erasergen.h"

EraserGen::EraserGen(ISheetCanvas *canvas) :
  ShapeGen(canvas),
  _shape_set()
{
}

void EraserGen::begin(const QPointF &p)
{
  _shape_set.clear();
  ShapeGen::begin(p);
  move(p);
}

void EraserGen::end(const QPointF &p)
{
  move(p);
  for (CommonShape *shape : _shape_set)
  {
    shape->updateClipHash();
  }
  _canvas->pushState();
  _canvas->updateSheetRect();
  _shape_set.clear();
}

void EraserGen::move(const QPointF &p)
{
  auto es = g_core->paint()->eraserSize() / _canvas->zoom();
  QSizeF size(es * 2, es * 2);
  QRectF beg(QPointF(_start.x() - es, _start.y() - es), size);
  QRectF end(QPointF(p.x() - es, p.y() - es), size);
  for (QQuickItem *item : _canvas->container()->childItems())
  {
    auto *shape = qobject_cast<CommonShape*>(item);
    if (shape)
    {
      if (shape->erase(beg, end))
      {
        _shape_set.insert(shape);
      }
    }
  }
  _start = p;
}
