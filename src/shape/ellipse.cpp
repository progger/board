/*
 * Copyright (C) 2012 Kulabuhov Michael, Kemerovo, Russia.
 *
 * See the LICENSE file for terms of use.
 */

#include <cmath>
#include <QVector2D>
#include <QRectF>
#include "pointarray.h"
#include "ellipse.h"

Ellipse::Ellipse()
{
}

void Ellipse::init(PointArray *point_array, QRectF *rect)
{
  center_ = QVector2D();
  rx_ = 1;
  ry_ = 1;
}

qreal Ellipse::getDeviation(PointArray *point_array)
{
  e_ = rx_ / ry_;
  qreal sum = 0;
  int count = point_array->count();
  for (int i = 0; i < count; i++)
  {
    sum += getDistance(point_array->at(i));
  }
  return sqrt(sum / count);
}

int Ellipse::getParamCount()
{
  return 4;
}

void Ellipse::changeParam(int param_num, int value, QRectF *rect)
{
  QVector2D c;
  switch (param_num)
  {
    case 0:
      c = QVector2D(center_.x() + value, center_.y());
      if (rect->contains(c.x(), c.y()))
      {
        center_ = c;
      }
      break;
    case 1:
      c = QVector2D(center_.x(), center_.y() + value);
      if (rect->contains(c.x(), c.y()))
      {
        center_ = c;
      }
      break;
    case 2:
      rx_ = qMax(rx_ + value, 1.0);
      break;
    case 3:
      ry_ = qMax(ry_ + value, 1.0);
      break;
  }
}

void Ellipse::fillPoints(PointArray *point_array)
{
  for (int i = 0; i < 65; i++)
  {
    qreal fi = 2 * M_PI * i / 64;
    QVector2D p(center_.x() + rx_ * sin(fi), center_.y() + ry_ * cos(fi));
    point_array->append(p);
  }
}

qreal Ellipse::getDistance(const QVector2D &p)
{
  qreal x = p.x() - center_.x();
  qreal y = (p.y() - center_.y()) * e_;
  qreal d = sqrt(x * x + y * y) - rx_;
  return d * d;
}
