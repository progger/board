/*
 * Copyright (C) 2012 Kulabuhov Michael, Kemerovo, Russia.
 *
 * See the LICENSE file for terms of use.
 */

#include <cmath>
#include <QRectF>
#include "pointarray.h"
#include "shape.h"
#include "shapehunter.h"

ShapeHunter::ShapeHunter(PointArray *point_array)
{
  point_array_ = point_array;
  QVector2D p = point_array_->at(0);
  QVector2D p1 = p;
  QVector2D p2 = p;
  int count = point_array->count();
  for (int i = 0; i < count; i++)
  {
    p = point_array->at(i);
    if (p.x() < p1.x())
      p1.setX(p.x());
    if (p.x() > p2.x())
      p2.setX(p.x());
    if (p.y() < p1.y())
      p1.setY(p.y());
    if (p.y() > p2.y())
      p2.setY(p.y());
  }
  rect_ = new QRectF(p1.x(), p1.y(), p2.x() - p1.x(), p2.y() - p1.y());
}

ShapeHunter::~ShapeHunter()
{
  delete rect_;
}

qreal ShapeHunter::hunt(Shape *shape)
{
  shape->init(point_array_, rect_);
  qreal deviation_current = shape->getDeviation(point_array_);
  while (true)
  {
    qreal deviation_base = deviation_current;
    int count = shape->getParamCount();
    for (int i = 0; i < count; i++)
    {
      shape->changeParam(i, 1, rect_);
      qreal deviation_plus = shape->getDeviation(point_array_);
      shape->changeParam(i, -2, rect_);
      qreal deviation_minus = shape->getDeviation(point_array_);
      shape->changeParam(i, 1, rect_);
      if (deviation_plus < deviation_base && deviation_plus < deviation_minus)
      {
        shape->changeParam(i, 1, rect_);
        deviation_current = deviation_plus;
      }
      else if (deviation_minus < deviation_base)
      {
        shape->changeParam(i, -1, rect_);
        deviation_current = deviation_minus;
      }
    }
    if (deviation_current >= deviation_base)
      return deviation_base;
  }
}
