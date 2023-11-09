/*
 * Copyright (C) 2012 Michael Kulabuhov, Kemerovo, Russia.
 *
 * See the LICENSE file for terms of use.
 */

#include <cmath>
#include "shapehunter.h"

using namespace PathProcessor;

ShapeHunter::ShapeHunter(Points *points) :
  _points(points)
{
  QPointF p = points->at(0);
  qreal x1 = p.x();
  qreal y1 = p.y();
  qreal x2 = p.x();
  qreal y2 = p.y();
  int count = points->size();
  for (int i = 1; i < count; ++i)
  {
    p = points->at(i);
    x1 = qMin(x1, p.x());
    y1 = qMin(y1, p.y());
    x2 = qMax(x2, p.x());
    y2 = qMax(y2, p.y());
  }
  _rect = QRectF(x1, y1, x2 - x1, y2 - y1);
}

qreal ShapeHunter::hunt(Shape *shape)
{
  shape->init(_points, &_rect);
  qreal deviation_current = shape->getDeviation(_points);
  while (true)
  {
    qreal deviation_base = deviation_current;
    int count = shape->getParamCount();
    for (int i = 0; i < count; i++)
    {
      shape->changeParam(i, 1, &_rect);
      qreal deviation_plus = shape->getDeviation(_points);
      shape->changeParam(i, -2, &_rect);
      qreal deviation_minus = shape->getDeviation(_points);
      shape->changeParam(i, 1, &_rect);
      if (deviation_plus < deviation_base && deviation_plus < deviation_minus)
      {
        shape->changeParam(i, 1, &_rect);
        deviation_current = deviation_plus;
      }
      else if (deviation_minus < deviation_base)
      {
        shape->changeParam(i, -1, &_rect);
        deviation_current = deviation_minus;
      }
    }
    if (deviation_current >= deviation_base)
      return deviation_base;
  }
}
