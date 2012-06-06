/*
 * Copyright (C) 2012 Kulabuhov Michael, Kemerovo, Russia.
 *
 * See the LICENSE file for terms of use.
 */

#ifndef SHAPEHUNTER_H
#define SHAPEHUNTER_H

#include <QtGlobal>

class PointArray;
class Shape;
class QRectF;

class ShapeHunter
{
public:
  ShapeHunter(PointArray *point_array);
  ~ShapeHunter();
  qreal hunt(Shape *shape);

private:
  PointArray *point_array_;
  QRectF *rect_;
};

#endif // SHAPEHUNTER_H
