/*
 * Copyright (C) 2013 Michael Kulabuhov, Kemerovo, Russia.
 *
 * See the LICENSE file for terms of use.
 */

#include <QQuickTextDocument>
#include "global.h"
#include "sheetcanvas.h"
#include "paint.h"
#include "textwrapper.h"
#include "textgen.h"

TextGen::TextGen(ISheetCanvas *canvas) :
  ShapeGen(canvas)
{
  SheetCanvas *canvas_obj = static_cast<SheetCanvas*>(canvas);
  _text_input = canvas_obj->textInput();
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
    TextWrapper *text = qobject_cast<TextWrapper*>(g_core->paint()->createShape("text", _canvas));
    Q_ASSERT(text);
    int font_size = g_core->paint()->fontSize();
    text->setColor(g_core->paint()->color());
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
    QQuickTextDocument *document = _text_input->property("textDocument").value<QQuickTextDocument*>();
    if (document && document->textDocument()->isEmpty())
    {
      delete _item;
    }
    else
    {
      _item->setWidth(_text_input->width() * _item->scalex());
      _item->setHeight(_text_input->height() * _item->scaley());
      _item->setInnerSize(QSizeF(_text_input->width(), _text_input->height()));
      _item->setProperty("text", _text_input->property("text"));
      _item->setVisible(true);
    }
    _item = nullptr;
    _canvas->pushState();
    _canvas->updateSheetRect();
  }
  _text_input->setProperty("textItem", QVariant());
}
