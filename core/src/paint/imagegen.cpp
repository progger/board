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

ImageGen::ImageGen(SheetCanvas *canvas, QSizeF image_size, QString image_data) :
  ShapeGen(canvas),
  _image_size(image_size),
  _image_data(image_data)
{
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

shared_ptr<ShapeGen> ImageGen::openFile(SheetCanvas *canvas)
{
  QFileDialog dialog;
  dialog.setAcceptMode(QFileDialog::AcceptOpen);
  dialog.setNameFilter("Image files (*.png *.jpg *.jpeg *.tif *.tiff *.gif *.svg)");
  if (!dialog.exec()) return nullptr;
  QString file_name = dialog.selectedFiles().first();
  QFileInfo file_info(file_name);
  QString ext = file_info.suffix();

  QString mime_type;
  if (ext == "png" || ext == "jpeg" || ext == "tiff" ||
      ext == "gif" || ext == "svg") {
    mime_type = ext;
  }
  else if (ext == "jpg") {
    mime_type = "jpg";
  }
  else if (ext == "tif") {
    mime_type = "tiff";
  }
  else {
    //TODO: error
    return nullptr;
  }

  QImage image(file_name);
  QFile file(file_name);
  if (!file.open(QIODevice::ReadOnly)) {
    //TODO: error
    return nullptr;
  }
  QByteArray data = file.readAll();
  QString image_data = "data:image/" + mime_type + ";base64," + data.toBase64();
  return make_shared<ImageGen>(canvas, image.size(), image_data);
}
