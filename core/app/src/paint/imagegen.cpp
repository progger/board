/*
 * Copyright (C) 2013 Kulabuhov Michael, Kemerovo, Russia.
 *
 * See the LICENSE file for terms of use.
 */

#include "global.h"
#include "paint.h"
#include "sheetcanvas.h"
#include "imagewrapper.h"
#include "imagegen.h"

using namespace std;

ImageGen::ImageGen(ISheetCanvas *canvas) :
  ShapeGen(canvas)
{
  SheetCanvas *canvas_obj = static_cast<SheetCanvas*>(canvas);
  _image_size = canvas_obj->paintObj()->imageSize();
  _image_hash = canvas_obj->paintObj()->imageHash();
}

void ImageGen::begin(const QPointF &p)
{
  QObject *obj = g_core->getComponent("qrc:/core/qml/ImageWrapper.qml")->create();
  ImageWrapper *image = qobject_cast<ImageWrapper*>(obj);
  Q_ASSERT(image);
  image->setParent(_canvas->container());
  image->setParentItem(_canvas->container());
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
