/*
 * Copyright (C) 2013 Michael Kulabuhov, Kemerovo, Russia.
 *
 * See the LICENSE file for terms of use.
 */

#include "global.h"
#include "paint.h"
#include "sheetcanvas.h"
#include "imagewrapper.h"
#include "imagegen.h"

ImageGen::ImageGen(ISheetCanvas *canvas) :
  ShapeGen(canvas)
{
  auto *canvas_obj = static_cast<SheetCanvas*>(canvas);
  _image_size = canvas_obj->paintObj()->imageSize();
  _image_hash = canvas_obj->paintObj()->imageHash();
}

void ImageGen::begin(const QPointF &p)
{
  auto *image = qobject_cast<ImageWrapper*>(g_core->paint()->createShape("image", _canvas));
  Q_ASSERT(image);
  image->setSize(_image_size);
  image->setInnerSize(_image_size);
  image->setHash(_image_hash);
  _item = image;
  move(p);
}

void ImageGen::end(const QPointF &p)
{
  ShapeGen::end(p);
  g_core->paint()->setMode("select");
}

void ImageGen::move(const QPointF &p)
{
  _item->setPosition(QPointF(p.x() - _item->width() / 2,
                             p.y() - _item->height() / 2));
}
