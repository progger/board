/*
 * Copyright (C) 2013 Kulabuhov Michael, Kemerovo, Russia.
 *
 * See the LICENSE file for terms of use.
 */

#include <QSGGeometryNode>
#include <QSGFlatColorMaterial>
#include "paintutils.h"
#include "ellipse.h"

Ellipse::Ellipse(QQuickItem *parent, float thinkness, QColor color) :
  Shape(parent, thinkness, color)
{
  setFlag(ItemHasContents);
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
  return node;
}

QString Ellipse::elementName() const
{
  return "ellipse";
}
