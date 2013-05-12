/*
 * Copyright (C) 2013 Kulabuhov Michael, Kemerovo, Russia.
 *
 * See the LICENSE file for terms of use.
 */

#ifndef IMAGEWRAPPER_H
#define IMAGEWRAPPER_H

#include "shape.h"

class ImageWrapper : public Shape
{
  Q_OBJECT
  Q_PROPERTY(QString imageData READ imageData WRITE setImageData NOTIFY imageDataChanged)
public:
  explicit ImageWrapper(QQuickItem *parent = 0);
  QString imageData() const { return _image_data; }
public slots:
  void setImageData(const QString &image_data);
signals:
  void imageDataChanged();
private:
  QString _image_data;
};

#endif // IMAGEWRAPPER_H
