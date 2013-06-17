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
  Ellipse();
  virtual void init(Points *, QRectF *);
  virtual qreal getDeviation(Points *points);
  virtual int getParamCount();
  virtual void changeParam(int param_num, int value, QRectF *rect);
  virtual void fillPoints(Points *points);
private:
  QPointF _center;
  qreal _rx;
  qreal _ry;
  qreal _e;

  qreal getDistance(const QPointF &p);
};

}

#endif // PP_ELLIPSE_H
