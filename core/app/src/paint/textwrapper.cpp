/*
 * Copyright (C) 2013 Michael Kulabuhov, Kemerovo, Russia.
 *
 * See the LICENSE file for terms of use.
 */

#include "textwrapper.h"

static QString DefaultFontFamily = "Arial";

TextWrapper::TextWrapper(QQuickItem *parent) :
  Shape(parent),
  _font_family(DefaultFontFamily),
  _font_size()
{
}

QObject *TextWrapper::textElement() const
{
  Q_ASSERT(childItems().size() == 1);
  return childItems()[0];
}

void TextWrapper::setText(const QString &text)
{
  _text = text;
  emit textChanged();
  updateInnerSize();
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
  updateInnerSize();
}

QString TextWrapper::elementName() const
{
  return "text";
}

void TextWrapper::innerSerialize(QXmlStreamWriter *writer, std::set<QString> *brd_objects) const
{
  Q_UNUSED(brd_objects);
  writer->writeAttribute("text", _text);
  writer->writeAttribute("font_family", _font_family);
  writer->writeAttribute("font_size", QString::number(_font_size));
}

void TextWrapper::innerDeserialize(QXmlStreamReader *reader)
{
  QXmlStreamAttributes attrs = reader->attributes();
  setText(attrs.value("text").toString());
  QString font_family = attrs.value("font_family").toString();
  if (font_family.isEmpty())
  {
    font_family = DefaultFontFamily;
  }
  setFontFamily(font_family);
  setFontSize(attrs.value("font_size").toString().toInt());
}

void TextWrapper::updateInnerSize()
{
  QObject *item = textElement();
  setInnerSize(QSizeF(item->property("contentWidth").toReal(),
                      item->property("contentHeight").toReal()));
}
