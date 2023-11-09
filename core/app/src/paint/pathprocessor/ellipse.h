/*
 * Copyright (C) 2012 Michael Kulabuhov, Kemerovo, Russia.
 *
 * See the LICENSE file for terms of use.
 */

#ifndef ELLIPSE_H
#define ELLIPSE_H

#include "shape.h"

namespace PathProcessor {

class Ellipse : public Shape
{
public:
  Ellipse() = default;
  void init(Points *, QRectF *) override;
  qreal getDeviation(Points *points) override;
  int getParamCount() override;
  void changeParam(int param_num, int value, QRectF *rect) override;
  void fillPoints(Points *points) override;
private:
  qreal getDistance(const QPointF &p);
private:
  QPointF _center;
  qreal _rx {};
  qreal _ry {};
  qreal _e {};
};

}

#endif // PP_ELLIPSE_H
