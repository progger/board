/*
 * Copyright (C) 2015 Michael Kulabuhov, Kemerovo, Russia.
 *
 * See the LICENSE file for terms of use.
 */

#include "global.h"
#include "swfplayer.h"

SwfPlayer::SwfPlayer(QQuickItem *parent) :
  Shape(parent)
{
  _swf_web_app = g_swf_web_app.lock();
  if (_swf_web_app.isNull())
  {
    _swf_web_app = QSharedPointer<SwfWebApp>::create();
    g_swf_web_app = _swf_web_app;
  }
}

int SwfPlayer::port() const
{
  return _swf_web_app->port();
}

void SwfPlayer::setHash(const QString &hash)
{
  _hash = hash;
  emit hashChanged();
}

QString SwfPlayer::elementName() const
{
  return "swf-player";
}

void SwfPlayer::innerSerialize(QXmlStreamWriter *writer, QSet<QString> *brd_objects) const
{
  Shape::innerSerialize(writer, brd_objects);
  writer->writeAttribute("version", QString::number(1));
  writer->writeAttribute("hash", _hash);
  if (brd_objects) brd_objects->insert(_hash);
}

void SwfPlayer::innerDeserialize(QXmlStreamReader *reader)
{
  Shape::innerDeserialize(reader);
  QXmlStreamAttributes attrs = reader->attributes();
  setHash(attrs.value("hash").toString());
}
