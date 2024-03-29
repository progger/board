/*
 * Copyright (C) 2012 Michael Kulabuhov, Kemerovo, Russia.
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
  qreal hunt(Shape *shape);
private:
  Points *_points;
  QRectF _rect;
};

}

#endif // SHAPEHUNTER_H
