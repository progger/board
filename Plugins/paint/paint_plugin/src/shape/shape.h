/*
 * Copyright (C) 2012 Kulabuhov Michael, Kemerovo, Russia.
 *
 * See the LICENSE file for terms of use.
 */

#ifndef SHAPE_H
#define SHAPE_H

#include <QtGlobal>

class PointArray;
class QRectF;

class Shape
{
public:
  virtual void init(PointArray *point_array, QRectF *rect) = 0;
  virtual qreal getDeviation(PointArray *point_array) = 0;
  virtual int getParamCount() = 0;
  virtual void changeParam(int param_num, int value, QRectF *rect) = 0;
  virtual void fillPoints(PointArray *point_array) = 0;
};

#endif // SHAPE_H
