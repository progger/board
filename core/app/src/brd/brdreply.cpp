/*
 * Copyright (C) 2013 Michael Kulabuhov, Kemerovo, Russia.
 *
 * See the LICENSE file for terms of use.
 */

#include <QTimer>
#include "brdreply.h"

BrdReply::BrdReply(const QByteArray &data, QObject *parent) :
  QNetworkReply(parent),
  _data(data),
  _offset(0)
{
  open(ReadOnly | Unbuffered);
  QTimer::singleShot(0, this, SIGNAL(readyRead()));
  QTimer::singleShot(0, this, SIGNAL(finished()));
}

qint64 BrdReply::bytesAvailable() const
{
  return _data.size() - _offset;
}

qint64 BrdReply::readData(char *data, qint64 maxlen)
{
  if (_offset >= _data.size()) return -1;
  if (!maxlen) return 0;
  qint64 len = std::min(_data.size() - _offset, maxlen);
  memcpy(data, _data.constData() + _offset, len);
  _offset += len;
  return len;
}
