/*
 * Copyright (C) 2015 Michael Kulabuhov, Kemerovo, Russia.
 *
 * See the LICENSE file for terms of use.
 */

#include "sheetcanvas.h"
#include "zoomgen.h"

ZoomGen::ZoomGen(ISheetCanvas *canvas) :
  ShapeGen(canvas),
  _last(0)
{
}

void ZoomGen::begin(const QPointF &p)
{
  _start = p;
  auto *canvas = static_cast<SheetCanvas*>(_canvas);
  _last = canvas->mouseY();
}

void ZoomGen::move(const QPointF &p)
{
  Q_UNUSED(p);
  auto *canvas = static_cast<SheetCanvas*>(_canvas);
  auto y = canvas->mouseY();
  auto ds = 1.0 + (_last - y) / 200.0;
  _last = canvas->mouseY();
  canvas->setZoom(canvas->zoom() * ds);
  QPointF dp = _start / ds - _start;
  canvas->moveSheet(dp.x(), dp.y());
}

void ZoomGen::end(const QPointF &p)
{
  move(p);
}
