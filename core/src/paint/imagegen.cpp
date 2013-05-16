/*
 * Copyright (C) 2013 Kulabuhov Michael, Kemerovo, Russia.
 *
 * See the LICENSE file for terms of use.
 */

#include <QFileDialog>
#include "paint.h"
#include "sheetcanvas.h"
#include "imagewrapper.h"
#include "imagegen.h"

using namespace std;

ImageGen::ImageGen(SheetCanvas *canvas) :
  ShapeGen(canvas)
{
  _image_data = canvas->paint()->imageData();
  _image_size = canvas->paint()->imageSize();
}

void ImageGen::begin(const QPointF &p)
{
  QObject *obj = _canvas->compImageWrapper()->create();
  ImageWrapper *image = qobject_cast<ImageWrapper*>(obj);
  Q_ASSERT(image);
  image->setParentItem(_canvas->container());
  image->setSize(_image_size);
  image->setInnerSize(_image_size);
  image->setImageData(_image_data);
  _item = image;
  move(p);
}

void ImageGen::end(const QPointF &p)
{
  ShapeGen::end(p);
  _canvas->paint()->setMode("select");
}

void ImageGen::move(const QPointF &p)
{
  _item->setPosition(QPointF(p.x() - _image_size.width() / 2,
                             p.y() - _image_size.height() / 2));
}
