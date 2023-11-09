/*
 * Copyright (C) 2012 Michael Kulabuhov, Kemerovo, Russia.
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
  void init(Points *, QRectF *) override;
  qreal getDeviation(Points *points) override;
  int getParamCount() override;
  void changeParam(int param_num, int value, QRectF *rect) override;
  void fillPoints(Points *points) override;
private:
  int _num_points;
  Points _points;

  qreal getDistance(const QPointF &p);
};

}

#endif // POLYGON_H
