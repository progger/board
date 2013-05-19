/*
 * Copyright (C) 2012 Kulabuhov Michael, Kemerovo, Russia.
 *
 * See the LICENSE file for terms of use.
 */

#include "shapehunter.h"
#include "shape.h"
#include "polygon.h"
#include "ellipse.h"
#include "pathprocessor.h"

using namespace PathProcessor;

void processPath(Points *points)
{
  if (points->size() <= 2) return;

  ShapeHunter hunter(points);
  qreal deviation;

  Polygon line(2);
  qreal best_deviation = hunter.hunt(&line);
  Shape *best_shape = &line;

  Polygon triangle(3);
  deviation = hunter.hunt(&triangle) * 3;
  if (deviation < best_deviation)
  {
    best_deviation = deviation;
    best_shape = &triangle;
  }

  Polygon quardangle(4);
  deviation = hunter.hunt(&quardangle) * 6;
  if (deviation < best_deviation)
  {
    best_deviation = deviation;
    best_shape = &quardangle;
  }

  Ellipse ellipse;
  deviation = hunter.hunt(&ellipse) * 2;
  if (deviation < best_deviation)
  {
    best_deviation = deviation;
    best_shape = &ellipse;
  }

  if (best_shape)
  {
    points->clear();
    best_shape->fillPoints(points);
  }
}
