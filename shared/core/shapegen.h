/*
 * Copyright (C) 2013 Michael Kulabuhov, Kemerovo, Russia.
 *
 * See the LICENSE file for terms of use.
 */

#ifndef SHAPEGEN_H
#define SHAPEGEN_H

#include <QQuickItem>
#include "isheetcanvas.h"

class Shape;

class ShapeGen
{
public:
  explicit ShapeGen(ISheetCanvas *canvas);
  virtual ~ShapeGen() {}
  virtual void begin(const QPointF &p);
  virtual void end(const QPointF &p);
  virtual void move(const QPointF &p);
protected:
  QPointF _start;
  ISheetCanvas *_canvas;
  Shape *_item;
};

#endif // SHAPEGEN_H
