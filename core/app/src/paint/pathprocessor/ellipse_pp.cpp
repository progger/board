/*
 * Copyright (C) 2012 Kulabuhov Michael, Kemerovo, Russia.
 *
 * See the LICENSE file for terms of use.
 */

#include <cmath>
#include "defs.h"
#include "../paintutils.h"
#include "ellipse.h"

using namespace PathProcessor;

Ellipse::Ellipse()
{
}

void Ellipse::init(Points *, QRectF *)
{
  _center = QPointF();
  _rx = 1;
  _ry = 1;
}

qreal Ellipse::getDeviation(Points *points)
{
  _e = _rx / _ry;
  qreal sum = 0;
  int count = points->size();
  for (int i = 0; i < count; i++)
  {
    sum += getDistance(points->at(i));
  }
  return sqrt(sum / count);
}

int Ellipse::getParamCount()
{
  return 4;
}

void Ellipse::changeParam(int param_num, int value, QRectF *rect)
{
  QPointF c;
  switch (param_num)
  {
    case 0:
      c = QPointF(_center.x() + value, _center.y());
      if (rect->contains(c))
      {
        _center = c;
      }
      break;
    case 1:
      c = QPointF(_center.x(), _center.y() + value);
      if (rect->contains(c))
      {
        _center = c;
      }
      break;
    case 2:
      _rx = qMax(_rx + value, 1.0);
      break;
    case 3:
      _ry = qMax(_ry + value, 1.0);
      break;
  }
}

void Ellipse::fillPoints(Points *points)
{
  int seg_count = getSegCount(qMax(_rx, _ry));
  for (int i = 0; i <= seg_count; ++i)
  {
    qreal fi = 2 * M_PI * i / seg_count;
    QPointF p(_center.x() + _rx * sin(fi), _center.y() + _ry * cos(fi));
    points->push_back(p);
  }
}

qreal Ellipse::getDistance(const QPointF &p)
{
  qreal x = p.x() - _center.x();
  qreal y = (p.y() - _center.y()) * _e;
  qreal d = sqrt(x * x + y * y) - _rx;
  return d * d;
}
