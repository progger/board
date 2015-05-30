/*
 * Copyright (C) 2015 Michael Kulabuhov, Kemerovo, Russia.
 *
 * See the LICENSE file for terms of use.
 */

#include "global.h"
#include "mimiotext.h"

MimioText::MimioText(QQuickItem *parent) :
  Shape(parent)
{
}

QString MimioText::text() const
{
  return QString::fromUtf8(g_core->brdStore()->getObject(_hash));
}

void MimioText::setHash(const QString &hash)
{
  _hash = hash;
  emit textChanged();
}

void MimioText::setText(const QString &text)
{
  _hash = g_core->brdStore()->addObject(text.toUtf8());
  emit textChanged();
}

QString MimioText::elementName() const
{
  return "mimio-text";
}

void MimioText::innerSerialize(QXmlStreamWriter *writer, QSet<QString> *brd_objects) const
{
  Shape::innerSerialize(writer, brd_objects);
  writer->writeAttribute("version", QString::number(1));
  writer->writeAttribute("hash", _hash);
  if (brd_objects) brd_objects->insert(_hash);
}

void MimioText::innerDeserialize(QXmlStreamReader *reader)
{
  Shape::innerDeserialize(reader);
  QXmlStreamAttributes attrs = reader->attributes();
  setHash(attrs.value("hash").toString());
}
