/*
 * Copyright (C) 2012 Kulabuhov Michael, Kemerovo, Russia.
 *
 * See the LICENSE file for terms of use.
 */

#include <cmath>
#include <QRectF>
#include "pointarray.h"
#include "utils.h"
#include "polygon.h"

Polygon::Polygon(int num_points) :
  Shape(),
  num_points_(num_points),
  points_(num_points)
{
}

void Polygon::init(PointArray *point_array, QRectF *rect)
{
  for (int i = 0; i < num_points_; i++)
    points_[i] = QVector2D();
}

qreal Polygon::getDeviation(PointArray *point_array)
{
  qreal sum = 0;
  int count = point_array->count();
  for (int i = 0; i < count; i++)
  {
    sum += getDistance(point_array->at(i));
  }
  return sqrt(sum / count);
}

int Polygon::getParamCount()
{
  return num_points_ * 2;
}

void Polygon::changeParam(int param_num, int value, QRectF *rect)
{
  int i = param_num / 2;
  QVector2D p = points_[i];
  if (param_num % 2)
    p.setY(p.y() + value);
  else
    p.setX(p.x() + value);
  if (rect->contains(p.x(), p.y()))
    points_[i] = p;
}

void Polygon::fillPoints(PointArray *point_array)
{
  for (int i = 0; i < num_points_; i++)
  {
    point_array->append(points_[i]);
  }
  if (num_points_ > 2)
  {
    point_array->append(points_[0]);
  }
}

qreal Polygon::getDistance(const QVector2D &p)
{
  qreal dist = distance(p, points_[0], points_[1]);
  if (num_points_ > 2)
  {
    for (int i = 1; i < num_points_ - 1; i++)
    {
      qreal d = distance(p, points_[i], points_[i + 1]);
      if (d < dist)
        dist = d;
    }
    qreal d = distance(p, points_[0], points_[num_points_ - 1]);
    if (d < dist)
      dist = d;
  }
  return dist;
}
