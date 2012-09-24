/*
 * Copyright (C) 2012 Kulabuhov Michael, Kemerovo, Russia.
 *
 * See the LICENSE file for terms of use.
 */

#ifndef ELLIPSE_H
#define ELLIPSE_H

#include "shape.h"

class QVector2D;

class Ellipse : public Shape
{
public:
  Ellipse();
  virtual void init(PointArray *point_array, QRectF *rect);
  virtual qreal getDeviation(PointArray *point_array);
  virtual int getParamCount();
  virtual void changeParam(int param_num, int value, QRectF *rect);
  virtual void fillPoints(PointArray *point_array);
private:
  QVector2D center_;
  qreal rx_;
  qreal ry_;
  qreal e_;

  qreal getDistance(const QVector2D &p);
};

#endif // ELLIPSE_H
