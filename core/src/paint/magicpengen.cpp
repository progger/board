/*
 * Copyright (C) 2013 Kulabuhov Michael, Kemerovo, Russia.
 *
 * See the LICENSE file for terms of use.
 */

#include "sheetcanvas.h"
#include "pen.h"
#include "pathprocessor/pathprocessor.h"
#include "magicpengen.h"

MagicPenGen::MagicPenGen(SheetCanvas *canvas) :
  PenGen(canvas)
{
}

void MagicPenGen::end(const QPointF &p)
{
  move(p);
  Pen *pen = static_cast<Pen*>(_item);
  Points &points = pen->points();
  processPath(&points);
  points.shrink_to_fit();
  QPointF &pnt = points[0];
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
  for (int i = 0; i < count; ++i)
  {
    QPointF &pnt = points[i];
    pnt.rx() -= x1;
    pnt.ry() -= y1;
  }
  pen->setPosition(QPointF(pen->x() + x1, pen->y() + y1));
  QSizeF size(x2 - x1, y2 - y1);
  pen->setSize(size);
  pen->setInnerSize(size);
  pen->update();
  pen->savePoints();
  _canvas->pushState();
  _canvas->updateSheetRect();
}
