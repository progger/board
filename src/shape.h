/*
 * Copyright (C) 2012 Kulabuhov Michael, Kemerovo, Russia.
 *
 * See the LICENSE file for terms of use.
 */

#ifndef SHAPE_H
#define SHAPE_H

#include <QtGlobal>

class QPointF;
class ParamArray;

class Shape
{
public:
  Shape(int param_count) : params_(param_count) {}
  ParamArray params() const { return params_; }
  virtual void init() const = 0;
  virtual qreal getDistance(const QPointF &point) const = 0;

private:
  ParamArray params_;
};

#endif // SHAPE_H
