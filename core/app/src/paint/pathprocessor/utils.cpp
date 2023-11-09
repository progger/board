/*
 * Copyright (C) 2012 Michael Kulabuhov, Kemerovo, Russia.
 *
 * See the LICENSE file for terms of use.
 */

#include <QVector2D>
#include "utils.h"
/*
qreal lengthSquared(const QPointF &p)
{
  return p.x() * p.x() + p.y() * p.y();
}
*/
qreal distance(const QVector2D &p, const QVector2D &p1, const QVector2D &p2)
{
  QVector2D v = p2 - p1;
  QVector2D w = p - p1;
  auto c1 = v.x() * w.x() + v.y() * w.y();
  if (c1 <= 0)
    return (p - p1).lengthSquared();
  auto c2 = v.lengthSquared();
  if (c2 <= c1)
    return (p - p2).lengthSquared();
  auto b = c1 / c2;
  QVector2D pb = w - b * v;
  return pb.lengthSquared();
}

qreal distance(const QPointF &p, const QPointF &p1, const QPointF &p2)
{
  /*
  QPointF v = p2 - p1;
  QPointF w = p - p1;
  qreal c1 = v.x() * w.x() + v.y() * w.y();
  if (c1 <= 0)
    return lengthSquared(p - p1);
  qreal c2 = lengthSquared(v);
  if (c2 <= c1)
    return lengthSquared(p - p2);
  qreal b = c1 / c2;
  QPointF pb = w - b * v;
  return lengthSquared(pb);
  */
  QVector2D vp(p);
  QVector2D vp1(p1);
  QVector2D vp2(p2);
  return distance(vp, vp1, vp2);
}
