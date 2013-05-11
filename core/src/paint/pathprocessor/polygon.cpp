/*
 * Copyright (C) 2012 Kulabuhov Michael, Kemerovo, Russia.
 *
 * See the LICENSE file for terms of use.
 */

#include <cmath>
#include "utils.h"
#include "polygon.h"

using namespace PathProcessor;

Polygon::Polygon(int num_points) :
  Shape(),
  _num_points(num_points),
  _points(num_points)
{
}

void Polygon::init(Points *, QRectF *)
{
  for (int i = 0; i < _num_points; i++)
  {
    qreal fi = 2 * M_PI * i / _num_points;
    _points[i] = QPointF(trunc(sin(fi) * 4), trunc(cos(fi) * 4));
  }
}

qreal Polygon::getDeviation(Points *points)
{
  qreal sum = 0;
  int count = points->size();
  for (int i = 0; i < count; i++)
  {
    sum += getDistance(points->at(i));
  }
  return sqrt(sum / count);
}

int Polygon::getParamCount()
{
  return _num_points * 2;
}

void Polygon::changeParam(int param_num, int value, QRectF *rect)
{
  int i = param_num / 2;
  QPointF p = _points[i];
  if (param_num % 2)
    p.setY(p.y() + value);
  else
    p.setX(p.x() + value);
  if (rect->contains(p.x(), p.y()))
    _points[i] = p;
}

void Polygon::fillPoints(Points *points)
{
  for (int i = 0; i < _num_points; i++)
  {
    points->push_back(_points[i]);
  }
  if (_num_points > 2)
  {
    points->push_back(_points[0]);
  }
}

qreal Polygon::getDistance(const QPointF &p)
{
  qreal dist = distance(p, _points[0], _points[1]);
  if (_num_points > 2)
  {
    for (int i = 1; i < _num_points - 1; i++)
    {
      qreal d = distance(p, _points[i], _points[i + 1]);
      if (d < dist)
        dist = d;
    }
    qreal d = distance(p, _points[0], _points[_num_points - 1]);
    if (d < dist)
      dist = d;
  }
  return dist;
}
