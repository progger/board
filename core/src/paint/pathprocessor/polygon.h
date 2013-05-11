/*
 * Copyright (C) 2012 Kulabuhov Michael, Kemerovo, Russia.
 *
 * See the LICENSE file for terms of use.
 */

#ifndef POLYGON_H
#define POLYGON_H

#include "shape.h"

namespace PathProcessor {

class Polygon : public Shape
{
public:
  Polygon(int num_points);
  virtual void init(Points *, QRectF *);
  virtual qreal getDeviation(Points *points);
  virtual int getParamCount();
  virtual void changeParam(int param_num, int value, QRectF *rect);
  virtual void fillPoints(Points *points);
private:
  int _num_points;
  Points _points;

  qreal getDistance(const QPointF &p);
};

}

#endif // POLYGON_H
