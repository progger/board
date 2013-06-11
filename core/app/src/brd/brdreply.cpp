/*
 * Copyright (C) 2013 Kulabuhov Michael, Kemerovo, Russia.
 *
 * See the LICENSE file for terms of use.
 */

#include <QTimer>
#include "brdstore.h"
#include "brdreply.h"

using namespace std;

BrdReply::BrdReply(shared_ptr<BrdObject> object, QObject *parent) :
  QNetworkReply(parent),
  _object(object),
  _offset(0)
{
  open(ReadOnly | Unbuffered);
  QTimer::singleShot(0, this, SIGNAL(readyRead()));
  QTimer::singleShot(0, this, SIGNAL(finished()));
}

qint64 BrdReply::bytesAvailable() const
{
  return _object->data().size() - _offset;
}

qint64 BrdReply::readData(char *data, qint64 maxlen)
{
  if (_offset >= _object->data().size()) return -1;
  if (!maxlen) return 0;
  qint64 len = qMin(_object->data().size() - _offset, maxlen);
  memcpy(data, _object->data().constData() + _offset, len);
  _offset += len;
  return len;
}
