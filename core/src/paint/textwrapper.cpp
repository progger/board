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
  QObject *item = textElement();
  _inner_size = QSizeF(item->property("contentWidth").toReal(),
                       item->property("contentHeight").toReal());
  emit scalexChanged();
  emit scaleyChanged();
}

void TextWrapper::setFontSize(int font_size)
{
  _font_size = font_size;
  emit fontSizeChanged();
}
