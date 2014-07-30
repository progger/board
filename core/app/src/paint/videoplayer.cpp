/*
 * Copyright (C) 2013 Michael Kulabuhov, Kemerovo, Russia.
 *
 * See the LICENSE file for terms of use.
 */

#include "../brd/brdstore.h"
#include "videoplayer.h"

VideoPlayer::VideoPlayer(QQuickItem *parent) :
  Shape(parent)
{
}

void VideoPlayer::setSource(const QString &source)
{
  _source = source;
  emit sourceChanged();
}

QString VideoPlayer::elementName() const
{
  return "video";
}

void VideoPlayer::innerSerialize(QXmlStreamWriter *writer, QSet<QString> *brd_objects) const
{
  Q_UNUSED(brd_objects);
  writer->writeAttribute("source", _source);
}

void VideoPlayer::innerDeserialize(QXmlStreamReader *reader)
{
  setSource(reader->attributes().value("source").toString());
}
