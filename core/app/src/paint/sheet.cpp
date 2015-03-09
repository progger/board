/*
 * Copyright (C) 2013 Michael Kulabuhov, Kemerovo, Russia.
 *
 * See the LICENSE file for terms of use.
 */

#include "sheet.h"

Sheet::Sheet(QQuickItem *parent) :
  QQuickItem(parent),
  _canvas(nullptr),
  _scrollable(true),
  _color(Qt::white)
{
}

void Sheet::setScrollable(bool scrollable)
{
  _scrollable = scrollable;
  emit scrollableChanged();
}

void Sheet::setColor(QColor color)
{
  _color = color;
  emit colorChanged();
}

void Sheet::serialize(QXmlStreamWriter *writer, QSet<QString> *brd_objects)
{
  writer->writeStartElement("sheet");
  writer->writeAttribute("scrollable", QString::number(_scrollable));
  writer->writeAttribute("color", QString("#%1").arg(_color.rgba(), 8, 16, QLatin1Char('0')));
  _canvas->serialize(writer, brd_objects);
  writer->writeEndElement();
}

void Sheet::deserialize(QXmlStreamReader *reader)
{
  if (reader->tokenType() != QXmlStreamReader::StartElement || reader->name() != "sheet") return;
  auto attrs = reader->attributes();
  if (attrs.hasAttribute("scrollable"))
    setScrollable(attrs.value("scrollable").toInt());
  if (attrs.hasAttribute("color"))
    setColor(attrs.value("color").toString());
  _canvas->deserialize(reader);
}

ISheetCanvas *Sheet::canvas()
{
  return _canvas;
}

void Sheet::componentComplete()
{
  QQuickItem::componentComplete();
  _canvas = findChild<SheetCanvas*>("sheetCanvas");
  Q_ASSERT(_canvas);
}
