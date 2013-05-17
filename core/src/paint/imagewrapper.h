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
  Q_PROPERTY(QString source READ source WRITE setSource NOTIFY sourceChanged)
public:
  explicit ImageWrapper(QQuickItem *parent = 0);
  QString source() const { return _source; }
public slots:
  void setSource(const QString &source);
signals:
  void sourceChanged();
private:
  QString _source;
};

#endif // IMAGEWRAPPER_H
