/*
 * Copyright (C) 2013 Michael Kulabuhov, Kemerovo, Russia.
 *
 * See the LICENSE file for terms of use.
 */

#include <QSGGeometryNode>
#include <QSGFlatColorMaterial>
#include "line.h"

Line::Line(QQuickItem *parent, float thinkness, QColor color) :
  Shape(parent, thinkness, color),
  _mode_ltrb(true)
{
  setFlag(ItemHasContents);
}

void Line::setModeLtrb(bool ltrb)
{
  _mode_ltrb = ltrb;
  update();
}

QSGNode *Line::updatePaintNode(QSGNode *old_node, QQuickItem::UpdatePaintNodeData *)
{
  QSGGeometryNode *node = static_cast<QSGGeometryNode *>(old_node);
  QSGGeometry *g;
  if (node)
  {
    g = node->geometry();
  }
  else
  {
    g = new QSGGeometry(QSGGeometry::defaultAttributes_Point2D(), 4);
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
  qreal x1 = 0;
  qreal y1 = _mode_ltrb ? 0 : innerSize().height() * scaley();
  qreal x2 = innerSize().width() * scalex();
  qreal y2 = _mode_ltrb ? innerSize().height() * scaley() : 0;
  qreal dx = x2 - x1;
  qreal dy = y2 - y1;
  qreal l = sqrt(dx * dx + dy * dy);
  qreal nx = -dy / l * tx;
  qreal ny = dx / l * ty;
  p[0].set(x1 + nx, y1 + ny);
  p[1].set(x1 - nx, y1 - ny);
  p[2].set(x2 + nx, y2 + ny);
  p[3].set(x2 - nx, y2 - ny);
  return node;
}

QString Line::elementName() const
{
  return "line";
}

void Line::innerSerialize(QXmlStreamWriter *writer, ISheetCanvas *, std::set<QString> *) const
{
  writer->writeAttribute("ltrb", QString::number(_mode_ltrb));
}

void Line::innerDeserialize(QXmlStreamReader *reader, ISheetCanvas *)
{
  _mode_ltrb = reader->attributes().value("ltrb").toString().toInt();
}
