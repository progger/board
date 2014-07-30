/*
 * Copyright (C) 2013 Michael Kulabuhov, Kemerovo, Russia.
 *
 * See the LICENSE file for terms of use.
 */

#include "pen.h"
#include "pathprocessor/pathprocessor.h"
#include "magicpengen.h"

MagicPenGen::MagicPenGen(ISheetCanvas *canvas) :
  PenGen(canvas)
{
}

void MagicPenGen::end(const QPointF &p)
{
  move(p);
  Pen *pen = static_cast<Pen*>(_item);
  Points &points = pen->points();
  QPointF pnt = points[0];
  qreal x1 = pnt.x();
  qreal y1 = pnt.y();
  qreal x2 = pnt.x();
  qreal y2 = pnt.y();
  int count = points.size();
  for (int i = 1; i < count; ++i)
  {
    QPointF &pnt = points[i];
    x1 = qMin(x1, pnt.x());
    y1 = qMin(y1, pnt.y());
    x2 = qMax(x2, pnt.x());
    y2 = qMax(y2, pnt.y());
  }
  qreal dx = -(x1 + x2) / 2;
  qreal dy = -(y1 + y2) / 2;
  for (int i = 0; i < count; ++i)
  {
    QPointF &pnt = points[i];
    pnt.rx() += dx;
    pnt.ry() += dy;
  }
  processPath(&points);
  points.squeeze();
  pnt = points[0];
  x1 = pnt.x();
  y1 = pnt.y();
  x2 = pnt.x();
  y2 = pnt.y();
  count = points.size();
  for (int i = 1; i < count; ++i)
  {
    QPointF &pnt = points[i];
    x1 = qMin(x1, pnt.x());
    y1 = qMin(y1, pnt.y());
    x2 = qMax(x2, pnt.x());
    y2 = qMax(y2, pnt.y());
  }
  for (int i = 0; i < count; ++i)
  {
    QPointF &pnt = points[i];
    pnt.rx() -= x1;
    pnt.ry() -= y1;
  }
  pen->setPosition(QPointF(pen->x() + x1 - dx, pen->y() + y1 - dy));
  QSizeF size(x2 - x1, y2 - y1);
  pen->setSize(size);
  pen->setInnerSize(size);
  pen->update();
  pen->savePoints();
  _canvas->pushState();
  _canvas->updateSheetRect();
}
