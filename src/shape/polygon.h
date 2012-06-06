/*
 * Copyright (C) 2012 Kulabuhov Michael, Kemerovo, Russia.
 *
 * See the LICENSE file for terms of use.
 */

#ifndef POLYGON_H
#define POLYGON_H

#include "shape.h"

class PointArray;
class QVector2D;

class Polygon : public Shape
{
public:
  Polygon(int num_points);
  virtual void init(PointArray *point_array, QRectF *rect);
  virtual qreal getDeviation(PointArray *point_array);
  virtual int getParamCount();
  virtual void changeParam(int param_num, int value, QRectF *rect);
  virtual void fillPoints(PointArray *point_array);
private:
  int num_points_;
  PointArray points_;

  qreal getDistance(const QVector2D &p);
};

#endif // POLYGON_H
