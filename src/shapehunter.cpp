/*
 * Copyright (C) 2012 Kulabuhov Michael, Kemerovo, Russia.
 *
 * See the LICENSE file for terms of use.
 */

#include <cmath>
#include "shapehunter.h"
#include "pointarray.h"
#include "paramarray.h"
#include "shape.h"

ShapeHunter::ShapeHunter(const PointArray &point_array) :
  point_array_(point_array)
{
}

qreal ShapeHunter::hunt(const Shape &shape)
{
  shape.init();
  ParamArray params = shape.params();
  int param_count = params.count();
  ParamArray delta(param_count);
  while (true)
  {
    qreal deveation_base = calcDeveation(shape);
    qreal delta_sum = 0;
    for (int i = 0; i < param_count; i++)
    {
      params[i] += 1;
      qreal deveation_plus = calcDeveation(shape);
      params[i] -= 2;
      qreal deveation_minus = calcDeveation(shape);
      params[i] += 1;
      if (deveation_plus < deveation_base)
        delta_sum += delta[i] = deveation_base - deveation_plus;
      else if (deveation_minus < deveation_base)
        delta_sum -= delta[i] = deveation_minus - deveation_base;
    }
    if (delta_sum == 0) return deveation_base;
    for (int i = 0; i < param_count; i++)
      params[i] += delta[i] / delta_sum;
  }
}

qreal ShapeHunter::calcDeveation(const Shape &shape)
{
  qreal sum = 0;
  foreach (QPointF point, point_array_)
  {
    qreal dist = shape.getDistance(point);
    sum += dist * dist;
  }
  return sqrt(sum / point_array_.count());
}
