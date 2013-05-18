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

void ImageWrapper::setSource(const QString &source)
{
  _source = source;
  emit sourceChanged();
}

QString ImageWrapper::elementName() const
{
  return "image";
}

void ImageWrapper::innerSerialize(QXmlStreamWriter *writer, SheetCanvas *) const
{
  writer->writeAttribute("source", _source);
}

void ImageWrapper::innerDeserialize(QXmlStreamReader *reader, SheetCanvas *)
{
  setSource(reader->attributes().value("source").toString());
}
