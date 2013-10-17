/*
 * Copyright (C) 2013 Michael Kulabuhov, Kemerovo, Russia.
 *
 * See the LICENSE file for terms of use.
 */

#include <QSGGeometryNode>
#include <QSGFlatColorMaterial>
#include "defs.h"
#include "paintutils.h"
#include "ellipse.h"

Ellipse::Ellipse(QQuickItem *parent, float thinkness, QColor color) :
  Shape(parent, thinkness, color)
{
  setFlag(ItemHasContents);
}

bool Ellipse::checkIntersect(const QRectF &rect)
{
  if (!Shape::checkIntersect(rect)) return false;
  qreal rx1 = rect.x();
  qreal ry1 = rect.y();
  qreal rx2 = rx1 + rect.width();
  qreal ry2 = ry1 + rect.height();
  qreal x1 = x();
  qreal y1 = y();
  qreal x2 = x1 + width();
  qreal y2 = y1 + height();
  if (rx1 <= x1 && ry1 < y1 && rx2 >= x2 && ry2 >= y2) return true;
  qreal cx = x1 + width() / 2;
  qreal cy = y1 + height() / 2;
  bool fx1 = rx1 <= cx && rx2 >= cx;
  bool fy1 = ry1 <= cy && ry2 >= cy;
  bool fx2 = (rx1 >= x1 && rx1 <= x2) || (rx2 >= x1 && rx2 <= x2);
  bool fy2 = (ry1 >= y1 && ry1 <= y2) || (ry2 >= y1 && ry2 <= y2);
  if ((fx1 && fy2) || (fy1 && fx2)) return true;
  qreal k = width() / height();
  qreal r = width() / 2;
  qreal xx1 = rx1 - cx;
  qreal yy1 = (ry1 - cy) * k;
  qreal xx2 = rx2 - cx;
  qreal yy2 = (ry2 - cy) * k;
  r = r * r;
  xx1 = xx1 * xx1;
  yy1 = yy1 * yy1;
  xx2 = xx2 * xx2;
  yy2 = yy2 * yy2;
  return xx1 + yy1 < r || xx1 + yy2 < r || yy2 + xx1 < r || yy2 + xx2 < r;
}

QSGNode *Ellipse::updatePaintNode(QSGNode *old_node, QQuickItem::UpdatePaintNodeData *)
{
  QSGGeometryNode *node = static_cast<QSGGeometryNode *>(old_node);
  QSGGeometry *g;
  if (node)
  {
    g = node->geometry();
  }
  else
  {
    g = new QSGGeometry(QSGGeometry::defaultAttributes_Point2D(), 0);
    g->setDrawingMode(GL_TRIANGLE_STRIP);
    QSGFlatColorMaterial *m = new QSGFlatColorMaterial;
    m->setColor(color());
    node = new QSGGeometryNode();
    node->setGeometry(g);
    node->setFlag(QSGNode::OwnsGeometry);
    node->setMaterial(m);
    node->setFlag(QSGNode::OwnsMaterial);
  }
  float r1 = width() / 2;
  float r2 = height() / 2;
  qreal tx = thickness() * scalex() / 2;
  qreal ty = thickness() * scaley() / 2;
  int seg_count = getSegCount(qMax(r1 + tx, r2 + ty));
  int vertex_count = (seg_count + 1) * 2;
  if (g->vertexCount() != vertex_count)
  {
    g->allocate(vertex_count);
  }
  auto p = g->vertexDataAsPoint2D();
  for (int i = 0; i <= seg_count; ++i)
  {
    qreal a = 2 * M_PI / seg_count * i;
    qreal kx = sin(a);
    qreal ky = cos(a);
    qreal x = r1 + (r1 + tx) * kx;
    qreal y = r2 + (r2 + ty) * ky;
    p[i * 2].set(x, y);
    x = r1 + (r1 - tx) * kx;
    y = r2 + (r2 - ty) * ky;
    p[i * 2 + 1].set(x, y);
  }
  node->markDirty(QSGNode::DirtyGeometry);
  return node;
}

QString Ellipse::elementName() const
{
  return "ellipse";
}
