/*
 * Copyright (C) 2013 Kulabuhov Michael, Kemerovo, Russia.
 *
 * See the LICENSE file for terms of use.
 */

#ifndef SHAPEGEN_H
#define SHAPEGEN_H

#include <QQuickItem>

class SheetCanvas;
class Paint;
class Shape;

class ShapeGen
{
public:
  explicit ShapeGen(SheetCanvas *canvas);
  virtual ~ShapeGen() {}
  Paint *paint() const;
  virtual void begin(const QPointF &p);
  virtual void end(const QPointF &p);
  virtual void move(const QPointF &p);
protected:
  QPointF _start;
  SheetCanvas *_canvas;
  Shape *_item;
};

#endif // SHAPEGEN_H
