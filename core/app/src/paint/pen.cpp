/*
 * Copyright (C) 2013 Michael Kulabuhov, Kemerovo, Russia.
 *
 * See the LICENSE file for terms of use.
 */

#include <QSGGeometryNode>
#include <QSGFlatColorMaterial>
#include "global.h"
#include "line.h"
#include "pen.h"

using namespace std;

Pen::Pen(QQuickItem *parent, float thinkness, QColor color, QColor bgcolor) :
  Shape(parent, thinkness, color, bgcolor),
  _points(),
  _hash()
{
}

void Pen::savePoints()
{
  QByteArray data;
  QDataStream stream(&data, QIODevice::WriteOnly);
  for (QPointF point : _points)
  {
    stream << point.x() << point.y();
  }
  _hash = g_core->brdStore()->addObject(data);
}

bool Pen::checkIntersect(const QRectF &rect)
{
  if (!Shape::checkIntersect(rect)) return false;
  qreal t = thickness() / 2 + 6;
  auto r = QRectF(rect.x() - t, rect.y() - t, rect.width() + t * 2, rect.height() + t * 2);
  int count = _points.size();
  for (int i = 0; i < count - 1; ++i)
  {
    auto p1 = QPointF(x() + _points[i].x() * scalex(), y() + _points[i].y() * scaley());
    auto p2 = QPointF(x() + _points[i + 1].x() * scalex(), y() + _points[i + 1].y() * scaley());
    if (Line::isLineIntersectRect(p1, p2, r)) return true;
  }
  return false;
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
    QSGFlatColorMaterial *m = new QSGFlatColorMaterial;
    m->setColor(color());
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
  qreal tx = thickness() * scalex() / 2;
  qreal ty = thickness() * scaley() / 2;
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
  node->markDirty(QSGNode::DirtyGeometry);
  return node;
}

QString Pen::elementName() const
{
  return "pen";
}

void Pen::innerSerialize(QXmlStreamWriter *writer, ISheetCanvas *, std::set<QString> *brd_objects) const
{
  writer->writeAttribute("hash", _hash);
  if (brd_objects) brd_objects->insert(_hash);
}

void Pen::innerDeserialize(QXmlStreamReader *reader, ISheetCanvas *)
{
  _points.clear();
  _hash = reader->attributes().value("hash").toString();
  QByteArray data = g_core->brdStore()->getObject(_hash);
  QDataStream stream(data);
  while (!stream.atEnd())
  {
    qreal x, y;
    stream >> x >> y;
    _points.push_back(QPointF(x, y));
  }
  _points.shrink_to_fit();
}
