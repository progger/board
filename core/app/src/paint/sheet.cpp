/*
 * Copyright (C) 2013 Michael Kulabuhov, Kemerovo, Russia.
 *
 * See the LICENSE file for terms of use.
 */

#include "sheet.h"

Sheet::Sheet(QQuickItem *parent) :
  QQuickItem(parent),
  _canvas(nullptr),
  _scrollable(true)
{
}

void Sheet::setScrollable(bool scrollable)
{
  _scrollable = scrollable;
  emit scrollableChanged();
}

void Sheet::serialize(QXmlStreamWriter *writer, QSet<QString> *brd_objects)
{
  writer->writeStartElement("sheet");
  writer->writeAttribute("scrollable", QString::number(_scrollable));
  _canvas->serialize(writer, brd_objects);
  writer->writeEndElement();
}

void Sheet::deserialize(QXmlStreamReader *reader)
{
  if (reader->tokenType() != QXmlStreamReader::StartElement || reader->name() != "sheet") return;
  auto attrs = reader->attributes();
  bool ok;
  setScrollable(attrs.value("scrollable").toInt(&ok) || !ok);
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
