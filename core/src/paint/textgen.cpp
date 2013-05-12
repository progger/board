/*
 * Copyright (C) 2013 Kulabuhov Michael, Kemerovo, Russia.
 *
 * See the LICENSE file for terms of use.
 */

#include "sheetcanvas.h"
#include "paint.h"
#include "textwrapper.h"
#include "textgen.h"

TextGen::TextGen(SheetCanvas *canvas) :
  ShapeGen(canvas)
{
  _text_input = _canvas->textInput();
  _text_input->setProperty("textGen", QVariant::fromValue<QObject*>(this));
}

TextGen::~TextGen()
{
  endEdit();
}

void TextGen::begin(const QPointF &)
{
}

void TextGen::end(const QPointF &p)
{
  endEdit();
  for (QQuickItem *item : _canvas->container()->childItems())
  {
    if (qobject_cast<TextWrapper*>(item) &&
        item->x() <= p.x() && item->x() + item->width() >= p.x() &&
        item->y() <= p.y() && item->y() + item->height() >= p.y())
    {
      _item = qobject_cast<Shape*>(item);
      break;
    }
  }
  if (!_item)
  {
    QObject *obj = _canvas->compTextWrapper()->create();
    TextWrapper *text = qobject_cast<TextWrapper*>(obj);
    Q_ASSERT(text);
    text->setParentItem(_canvas->container());
    int font_size = _canvas->paint()->fontSize();
    text->setColor(_canvas->paint()->color());
    text->setFontSize(font_size);
    text->setPosition(QPointF(p.x(), p.y() - font_size / 2));
    text->setSize(text->innerSize());
    _item = text;
  }
  _item->setVisible(false);
  _text_input->setProperty("textItem", QVariant::fromValue<QObject*>(_item));
  _text_input->setFocus(true);
}

void TextGen::move(const QPointF &)
{
}

void TextGen::endEdit()
{
  if (_item)
  {
    _item->setWidth(_text_input->width() * _item->scalex());
    _item->setHeight(_text_input->height() * _item->scaley());
    _item->setProperty("text", _text_input->property("text"));
    _item->setVisible(true);
    _item = nullptr;
  }
  _text_input->setProperty("textItem", QVariant());
}
