/*
 * Copyright (C) 2013 Kulabuhov Michael, Kemerovo, Russia.
 *
 * See the LICENSE file for terms of use.
 */

#include "QSGGeometryNode"
#include "QSGFlatColorMaterial"
#include "rectangle.h"

Rectangle::Rectangle(QQuickItem *parent, float thinkness, QColor color) :
  Shape(parent, thinkness, color)
{
  setFlag(ItemHasContents);
}

QSGNode *Rectangle::updatePaintNode(QSGNode *old_node, QQuickItem::UpdatePaintNodeData *)
{
  QSGGeometryNode *node = static_cast<QSGGeometryNode *>(old_node);
  QSGGeometry *g;
  if (node)
  {
    g = node->geometry();
  }
  else
  {
    g = new QSGGeometry(QSGGeometry::defaultAttributes_Point2D(), 10);
    g->setDrawingMode(GL_TRIANGLE_STRIP);
    QSGFlatColorMaterial *m = new QSGFlatColorMaterial;
    m->setColor(color());
    node = new QSGGeometryNode();
    node->setGeometry(g);
    node->setFlag(QSGNode::OwnsGeometry);
    node->setMaterial(m);
    node->setFlag(QSGNode::OwnsMaterial);
  }
  auto p = g->vertexDataAsPoint2D();
  float tx = thickness() * scalex() / 2;
  float ty = thickness() * scaley() / 2;
  p[0].set(-tx, -ty);
  p[1].set(tx, ty);
  p[2].set(width() + tx, -ty);
  p[3].set(width() - tx, ty);
  p[4].set(width() + tx, height() + ty);
  p[5].set(width() - tx, height() - ty);
  p[6].set(-tx, height() + ty);
  p[7].set(tx, height() - ty);
  p[8].set(-tx, -ty);
  p[9].set(tx, ty);
  return node;
}
