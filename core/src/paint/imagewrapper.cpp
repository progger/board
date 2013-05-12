/*
 * Copyright (C) 2013 Kulabuhov Michael, Kemerovo, Russia.
 *
 * See the LICENSE file for terms of use.
 */

#include "imagewrapper.h"

ImageWrapper::ImageWrapper(QQuickItem *parent) :
  Shape(parent)
{
}

void ImageWrapper::setImageData(const QString &image_data)
{
  _image_data = image_data;
  emit imageDataChanged();
}
