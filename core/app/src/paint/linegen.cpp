/*
 * Copyright (C) 2013 Michael Kulabuhov, Kemerovo, Russia.
 *
 * See the LICENSE file for terms of use.
 */

#include "paintutils.h"
#include "line.h"
#include "linegen.h"

LineGen::LineGen(ISheetCanvas *canvas) :
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
