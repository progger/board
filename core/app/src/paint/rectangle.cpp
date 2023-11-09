/*
 * Copyright (C) 2013 Michael Kulabuhov, Kemerovo, Russia.
 *
 * See the LICENSE file for terms of use.
 */

#include <QSGGeometryNode>
#include <QSGFlatColorMaterial>
#include "rectangle.h"

Rectangle::Rectangle(QQuickItem *parent, float thinkness, QColor color, QColor bgcolor) :
  CommonShape(parent, thinkness, std::move(color), std::move(bgcolor))
{
}

void Rectangle::updateMainNode(QSGGeometryNode *node)
{
  QSGGeometry *g = node->geometry();
  if (!g)
  {
    g = new QSGGeometry(QSGGeometry::defaultAttributes_Point2D(), 10);
    g->setDrawingMode(GL_TRIANGLE_STRIP);
    node->setGeometry(g);
    node->setFlag(QSGNode::OwnsGeometry);
  }
  auto *p = g->vertexDataAsPoint2D();
  auto tx = static_cast<float>(thickness() * scalex() / 2);
  auto ty = static_cast<float>(thickness() * scaley() / 2);
  auto w = static_cast<float>(width());
  auto h = static_cast<float>(height());
  p[0].set(-tx, -ty);
  p[1].set(tx, ty);
  p[2].set(w + tx, -ty);
  p[3].set(w - tx, ty);
  p[4].set(w + tx, h + ty);
  p[5].set(w - tx, h - ty);
  p[6].set(-tx, h + ty);
  p[7].set(tx, h - ty);
  p[8].set(-tx, -ty);
  p[9].set(tx, ty);
}

void Rectangle::updateBackgroundNode(QSGGeometryNode *node)
{
  QSGGeometry *g = node->geometry();
  if (!g)
  {
    g = new QSGGeometry(QSGGeometry::defaultAttributes_Point2D(), 4);
    g->setDrawingMode(GL_TRIANGLE_STRIP);
    node->setGeometry(g);
    node->setFlag(QSGNode::OwnsGeometry);
  }
  auto *p = g->vertexDataAsPoint2D();
  auto w = static_cast<float>(width());
  auto h = static_cast<float>(height());
  p[0].set(0, 0);
  p[1].set(0, h);
  p[2].set(w, 0);
  p[3].set(w, h);
}

QString Rectangle::elementName() const
{
  return "rectangle";
}
