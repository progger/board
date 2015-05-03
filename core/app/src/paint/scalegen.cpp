/*
 * Copyright (C) 2015 Michael Kulabuhov, Kemerovo, Russia.
 *
 * See the LICENSE file for terms of use.
 */

#include "global.h"
#include "sheetcanvas.h"
#include "scalegen.h"

ScaleGen::ScaleGen(ISheetCanvas *canvas) :
  ShapeGen(canvas)
{
}

void ScaleGen::begin(const QPointF &p)
{
  _start = p;
  SheetCanvas *canvas = static_cast<SheetCanvas*>(_canvas);
  _last = canvas->mouseY();
}

void ScaleGen::move(const QPointF &p)
{
  Q_UNUSED(p);
  SheetCanvas *canvas = static_cast<SheetCanvas*>(_canvas);
  float y = canvas->mouseY();
  float ds = 1 + (_last - y) / 200;
  _last = canvas->mouseY();
  IPaint *paint = g_core->paint();
  paint->setScale(paint->scale() * ds);
  QPointF dp = _start - _start / ds;
  canvas->moveSheet(dp.x(), dp.y());
  _start -= dp;
}

void ScaleGen::end(const QPointF &p)
{
  move(p);
}
