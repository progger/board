/*
 * Copyright (C) 2012 Kulabuhov Michael, Kemerovo, Russia.
 *
 * See the LICENSE file for terms of use.
 */

#ifndef HUNTER_H
#define HUNTER_H

#include <QtGlobal>

class Shape;
class PointArray;
class ParamArray;

class ShapeHunter
{
public:
  ShapeHunter(const PointArray &point_array);
  qreal hunt(const Shape &shape);

private:
  const PointArray &point_array_;

  qreal calcDeveation(const Shape &shape);
};

#endif // HUNTER_H
