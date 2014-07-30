/*
 * Copyright (C) 2013 Michael Kulabuhov, Kemerovo, Russia.
 *
 * See the LICENSE file for terms of use.
 */

#include <QSGGeometryNode>
#include <QSGFlatColorMaterial>
#include "line.h"

static bool cmpIntr(qreal Ax, qreal Ay, qreal Bx, qreal By,
                    qreal Cx, qreal Cy, qreal Dx, qreal Dy)
{
  qreal r = ((Ay - Cy) * (Dx - Cx) - (Ax - Cx) * (Dy - Cy)) /
            ((Bx - Ax) * (Dy - Cy) - (By - Ay) * (Dx - Cx));
  qreal s = ((Ay - Cy) * (Bx - Ax) - (Ax - Cx) * (By - Ay)) /
            ((Bx - Ax) * (Dy - Cy) - (By - Ay) * (Dx - Cx));
  return r >= 0 && r <= 1 && s >= 0 && s <= 1;
}

Line::Line(QQuickItem *parent, float thinkness, QColor color, QColor bgcolor) :
  CommonShape(parent, thinkness, color, bgcolor),
  _p1(),
  _p2()
{
}

bool Line::checkIntersect(const QRectF &rect)
{
  if (!Shape::checkIntersect(rect)) return false;
  qreal t = thickness() / 2 + 6;
  auto p1 = QPointF(x() + _p1.x() * scalex(), y() + _p1.y() * scaley());
  auto p2 = QPointF(x() + _p2.x() * scalex(), y() + _p2.y() * scaley());
  auto r = QRectF(rect.x() - t, rect.y() - t, rect.width() + t * 2, rect.height() + t * 2);
  return isLineIntersectRect(p1, p2, r);
}

int Line::computeCohenOutcode(const QPointF &p, const QRectF &rect)
{
  int code = 0;
  if (p.y() > rect.bottom()) code = 8;
  else if(p.y() < rect.top()) code = 4;
  if(p.x() > rect.right()) return code + 2;
  else if(p.x() < rect.left()) return code + 1;
  return code;
}

bool Line::isLineIntersectRect(const QPointF &p1, const QPointF &p2, const QRectF &rect)
{
  int outcode_p1 = computeCohenOutcode(p1, rect);
  if (outcode_p1 == 0) return true;
  int outcode_p2 = computeCohenOutcode(p2, rect);
  if (outcode_p2 == 0) return true;
  if ((outcode_p1 & outcode_p2) != 0) return false;
  if ((outcode_p1 + outcode_p2) == 12) return true;
  if ((outcode_p1 + outcode_p2) == 3) return true;

  return
      cmpIntr(p1.x(), p1.y(), p2.x(), p2.y(), rect.left(), rect.bottom(), rect.right(), rect.bottom()) ||
      cmpIntr(p1.x(), p1.y(), p2.x(), p2.y(), rect.left(), rect.top(), rect.right(), rect.top()) ||
      cmpIntr(p1.x(), p1.y(), p2.x(), p2.y(), rect.left(), rect.top(), rect.left(), rect.bottom()) ||
      cmpIntr(p1.x(), p1.y(), p2.x(), p2.y(), rect.right(), rect.top(), rect.right(), rect.bottom());
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

void Line::updateMainNode(QSGGeometryNode *node)
{
  QSGGeometry *g = node->geometry();
  if (!g)
  {
    g = new QSGGeometry(QSGGeometry::defaultAttributes_Point2D(), 4);
    g->setDrawingMode(GL_TRIANGLE_STRIP);
    node->setGeometry(g);
    node->setFlag(QSGNode::OwnsGeometry);
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
}

QString Line::elementName() const
{
  return "line";
}

void Line::innerSerialize(QXmlStreamWriter *writer, QSet<QString> *brd_objects) const
{
  CommonShape::innerSerialize(writer, brd_objects);
  writer->writeAttribute("x1", QString::number(_p1.x()));
  writer->writeAttribute("y1", QString::number(_p1.y()));
  writer->writeAttribute("x2", QString::number(_p2.x()));
  writer->writeAttribute("y2", QString::number(_p2.y()));
}

void Line::innerDeserialize(QXmlStreamReader *reader)
{
  CommonShape::innerDeserialize(reader);
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
