/*
 * Copyright (C) 2013 Kulabuhov Michael, Kemerovo, Russia.
 *
 * See the LICENSE file for terms of use.
 */

#include "textwrapper.h"

TextWrapper::TextWrapper(QQuickItem *parent) :
  Shape(parent),
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

void TextWrapper::innerSerialize(QXmlStreamWriter *writer, ISheetCanvas *, std::set<QString> *) const
{
  writer->writeAttribute("text", _text);
  writer->writeAttribute("font_size", QString::number(_font_size));
}

void TextWrapper::innerDeserialize(QXmlStreamReader *reader, ISheetCanvas *)
{
  QXmlStreamAttributes attrs = reader->attributes();
  setText(attrs.value("text").toString());
  setFontSize(attrs.value("font_size").toString().toInt());
}

void TextWrapper::updateInnerSize()
{
  QObject *item = textElement();
  setInnerSize(QSizeF(item->property("contentWidth").toReal(),
                      item->property("contentHeight").toReal()));
}
