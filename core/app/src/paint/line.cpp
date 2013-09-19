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
  _p1(),
  _p2()
{
  setFlag(ItemHasContents);
}

void Line::setP1(const QPointF &p)
{
  _p1 = p;
  update();
}

void Line::setP2(const QPointF &p)
{
  _p2 = p;
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
  qreal x1 = _p1.x() * scalex();
  qreal y1 = _p1.y() * scaley();
  qreal x2 = _p2.x() * scalex();
  qreal y2 = _p2.y() * scaley();
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
  writer->writeAttribute("x1", QString::number(_p1.x()));
  writer->writeAttribute("y1", QString::number(_p1.y()));
  writer->writeAttribute("x2", QString::number(_p2.x()));
  writer->writeAttribute("y2", QString::number(_p2.y()));
}

void Line::innerDeserialize(QXmlStreamReader *reader, ISheetCanvas *)
{
  if (reader->attributes().hasAttribute("ltrb"))
  {
    // Убрать через некоторое время
    bool mode_ltrb = reader->attributes().value("ltrb").toString().toInt();
    _p1.setX(0);
    _p2.setY(innerSize().width());
    if (mode_ltrb)
    {
      _p1.setY(0);
      _p2.setY(innerSize().height());
    }
    else
    {
      _p1.setY(innerSize().height());
      _p2.setY(0);
    }
  }
  else
  {
    _p1.setX(reader->attributes().value("x1").toString().toDouble());
    _p1.setY(reader->attributes().value("y1").toString().toDouble());
    _p2.setX(reader->attributes().value("x2").toString().toDouble());
    _p2.setY(reader->attributes().value("y2").toString().toDouble());
  }
}
