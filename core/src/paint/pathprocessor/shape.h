/*
 * Copyright (C) 2012 Kulabuhov Michael, Kemerovo, Russia.
 *
 * See the LICENSE file for terms of use.
 */

#ifndef SHAPE_H
#define SHAPE_H

#include <QRectF>
#include "points.h"

namespace PathProcessor {

class Shape
{
public:
  virtual void init(Points *points_, QRectF *rect) = 0;
  virtual qreal getDeviation(Points *points) = 0;
  virtual int getParamCount() = 0;
  virtual void changeParam(int param_num, int value, QRectF *rect) = 0;
  virtual void fillPoints(Points *points) = 0;
};

}

#endif // SHAPE_H
