/*
 * Copyright (C) 2013 Kulabuhov Michael, Kemerovo, Russia.
 *
 * See the LICENSE file for terms of use.
 */

#include "sheetcanvas.h"
#include "paintutils.h"
#include "line.h"
#include "linegen.h"

LineGen::LineGen(SheetCanvas *canvas) :
  ShapeGen(canvas)
{
}

void LineGen::begin(const QPointF &p)
{
  ShapeGen::begin(p);
  _item = createItem<Line>(_canvas, p);
}

void LineGen::move(const QPointF &p)
{
  ShapeGen::move(p);
  Line *line = qobject_cast<Line*>(_item);
  Q_ASSERT(line);
  line->setModeLtrb((_start.x() < p.x()) == (_start.y() < p.y()));
}