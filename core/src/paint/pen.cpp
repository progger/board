/*
 * Copyright (C) 2013 Kulabuhov Michael, Kemerovo, Russia.
 *
 * See the LICENSE file for terms of use.
 */

#include "QSGGeometryNode"
#include "QSGFlatColorMaterial"
#include "pen.h"

Pen::Pen(QQuickItem *parent, float thinkness, QColor color) :
  Shape(parent, thinkness, color),
  _points()
{
  setFlag(ItemHasContents);
  setAntialiasing(true);
}

QSGNode *Pen::updatePaintNode(QSGNode *old_node, QQuickItem::UpdatePaintNodeData *)
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
    g->setLineWidth(_thickness);
    QSGFlatColorMaterial *m = new QSGFlatColorMaterial;
    m->setColor(_color);
    node = new QSGGeometryNode();
    node->setGeometry(g);
    node->setFlag(QSGNode::OwnsGeometry);
    node->setMaterial(m);
    node->setFlag(QSGNode::OwnsMaterial);
  }
  int count = _points.size();
  int vertex_count = qMax((count - 1) * 4, 0);
  if (g->vertexCount() != vertex_count)
  {
    g->allocate(vertex_count);
  }
  auto p = g->vertexDataAsPoint2D();
  qreal tx = _thickness * scalex() / 2;
  qreal ty = _thickness * scaley() / 2;
  for (int i = 0; i < count - 1; ++i)
  {
    qreal x1 = _points[i].x() * scalex();
    qreal y1 = _points[i].y() * scaley();
    qreal x2 = _points[i + 1].x() * scalex();
    qreal y2 = _points[i + 1].y() * scaley();
    qreal dx = x2 - x1;
    qreal dy = y2 - y1;
    qreal l = sqrt(dx * dx + dy * dy);
    qreal nx = -dy / l * tx;
    qreal ny = dx / l * ty;
    int n = i * 4;
    p[n].set(x1 + nx, y1 + ny);
    p[n + 1].set(x1 - nx, y1 - ny);
    p[n + 2].set(x2 + nx, y2 + ny);
    p[n + 3].set(x2 - nx, y2 - ny);
  }
  return node;
}
