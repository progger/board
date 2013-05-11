/*
 * Copyright (C) 2012 Kulabuhov Michael, Kemerovo, Russia.
 *
 * See the LICENSE file for terms of use.
 */

#ifndef SHAPEHUNTER_H
#define SHAPEHUNTER_H

#include <QRectF>
#include "points.h"
#include "shape.h"

namespace PathProcessor {

class ShapeHunter
{
public:
  ShapeHunter(Points *points);
  ~ShapeHunter();
  qreal hunt(Shape *shape);

private:
  Points *_points;
  QRectF *_rect;
};

}

#endif // SHAPEHUNTER_H
