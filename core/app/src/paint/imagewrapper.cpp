/*
 * Copyright (C) 2013 Kulabuhov Michael, Kemerovo, Russia.
 *
 * See the LICENSE file for terms of use.
 */

#include "../brd/brdstore.h"
#include "imagewrapper.h"

ImageWrapper::ImageWrapper(QQuickItem *parent) :
  Shape(parent)
{
}

QString ImageWrapper::source() const
{
  return BrdObject::urlString(_hash);
}

void ImageWrapper::setHash(const QString &hash)
{
  _hash = hash;
  emit sourceChanged();
}

QString ImageWrapper::elementName() const
{
  return "image";
}

void ImageWrapper::innerSerialize(QXmlStreamWriter *writer, SheetCanvas *, std::set<QString> *brd_objects) const
{
  writer->writeAttribute("hash", _hash);
  if (brd_objects) brd_objects->insert(_hash);
}

void ImageWrapper::innerDeserialize(QXmlStreamReader *reader, SheetCanvas *)
{
  setHash(reader->attributes().value("hash").toString());
}
