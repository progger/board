/*
 * Copyright (C) 2013 Michael Kulabuhov, Kemerovo, Russia.
 *
 * See the LICENSE file for terms of use.
 */

#include "global.h"
#include "imagewrapper.h"

ImageWrapper::ImageWrapper(QQuickItem *parent) :
  Shape(parent)
{
}

QString ImageWrapper::source() const
{
  return g_core->brdStore()->getUrlString(_hash);
}

void ImageWrapper::setHash(const QString &hash)
{
  _hash = hash;
  emit hashChanged();
}

QString ImageWrapper::elementName() const
{
  return "image";
}

void ImageWrapper::innerSerialize(QXmlStreamWriter *writer, QSet<QString> *brd_objects) const
{
  Shape::innerSerialize(writer, brd_objects);
  writer->writeAttribute("version", QString::number(1));
  writer->writeAttribute("hash", _hash);
  if (brd_objects) brd_objects->insert(_hash);
}

void ImageWrapper::innerDeserialize(QXmlStreamReader *reader)
{
  Shape::innerDeserialize(reader);
  setHash(reader->attributes().value("hash").toString());
}
