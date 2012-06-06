/*
 * Copyright (C) 2012 Kulabuhov Michael, Kemerovo, Russia.
 *
 * See the LICENSE file for terms of use.
 */

#include "utils.h"

qreal distance(const QVector2D &p, const QVector2D &p1, const QVector2D &p2)
{
  QVector2D v = p2 - p1;
  QVector2D w = p - p1;
  qreal c1 = v.x() * w.x() + v.y() * w.y();
  if (c1 <= 0)
    return (p - p1).lengthSquared();
  qreal c2 = v.lengthSquared();
  if (c2 <= c1)
    return (p - p2).lengthSquared();
  qreal b = c1 / c2;
  QVector2D pb = w - b * v;
  return pb.lengthSquared();
}
