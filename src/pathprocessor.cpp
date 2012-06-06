/*
 * Copyright (C) 2012 Kulabuhov Michael, Kemerovo, Russia.
 *
 * See the LICENSE file for terms of use.
 */

#include "shape/shapehunter.h"
#include "shape/pointarray.h"
#include "shape/shape.h"
#include "shape/polygon.h"
#include "pathprocessor.h"

PathProcessor::PathProcessor(QObject *parent) :
  QObject(parent),
  arx_(),
  ary_()
{
}

bool PathProcessor::process(QVariantList arx, QVariantList ary)
{
  clear();
  int count = qMin(arx.count(), ary.count());
  PointArray point_array(count);
  for (int i = 0; i < count; i++)
  {
    QVector2D point(arx[i].toReal(), ary[i].toReal());
    point_array[i] = point;
  }

  ShapeHunter hunter(&point_array);
  qreal deviation;

  Polygon line(2);
  qreal best_deviation = hunter.hunt(&line);
  Shape *best_shape = &line;

  Polygon triangle(3);
  deviation = hunter.hunt(&triangle) * 2;
  if (deviation < best_deviation)
  {
    best_deviation = deviation;
    best_shape = &triangle;
  }

  if (best_shape)
  {
    PointArray result_array;
    best_shape->fillPoints(&result_array);
    count = result_array.count();
    for (int i = 0; i < count; i++)
    {
      QVector2D point = result_array[i];
      arx_.append(point.x());
      ary_.append(point.y());
    }
    return true;
  }

  return false;
}

void PathProcessor::clear()
{
  arx_.clear();
  ary_.clear();
}
