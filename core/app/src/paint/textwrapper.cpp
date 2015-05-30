/*
 * Copyright (C) 2013 Michael Kulabuhov, Kemerovo, Russia.
 *
 * See the LICENSE file for terms of use.
 */

#include "global.h"
#include "textwrapper.h"

static QString DefaultFontFamily = "Arial";

TextWrapper::TextWrapper(QQuickItem *parent) :
  Shape(parent),
  _font_family(DefaultFontFamily),
  _font_size()
{
}

QString TextWrapper::text() const
{
  return QString::fromUtf8(g_core->brdStore()->getObject(_hash));
}

void TextWrapper::setHash(const QString &hash)
{
  _hash = hash;
  emit textChanged();
}

void TextWrapper::setText(const QString &text)
{
  _hash = g_core->brdStore()->addObject(text.toUtf8());
  emit textChanged();
}

void TextWrapper::setFontFamily(const QString &font_family)
{
  _font_family = font_family;
  emit fontFamilyChanged();
}

void TextWrapper::setFontSize(int font_size)
{
  _font_size = font_size;
  emit fontSizeChanged();
}

QString TextWrapper::elementName() const
{
  return "text";
}

void TextWrapper::innerSerialize(QXmlStreamWriter *writer, QSet<QString> *brd_objects) const
{
  Shape::innerSerialize(writer, brd_objects);
  writer->writeAttribute("version", QString::number(1));
  writer->writeAttribute("hash", _hash);
  writer->writeAttribute("font_family", _font_family);
  writer->writeAttribute("font_size", QString::number(_font_size));
  if (brd_objects) brd_objects->insert(_hash);
}

void TextWrapper::innerDeserialize(QXmlStreamReader *reader)
{
  Shape::innerDeserialize(reader);
  QXmlStreamAttributes attrs = reader->attributes();
  int version = attrs.value("version").toInt();
  if (version >= 1)
  {
    setHash(attrs.value("hash").toString());
  }
  else
  {
    setText(attrs.value("text").toString());
  }
  QString font_family = attrs.value("font_family").toString();
  if (font_family.isEmpty())
  {
    font_family = DefaultFontFamily;
  }
  setFontFamily(font_family);
  setFontSize(attrs.value("font_size").toString().toInt());
}
