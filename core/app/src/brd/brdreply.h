/*
 * Copyright (C) 2013 Kulabuhov Michael, Kemerovo, Russia.
 *
 * See the LICENSE file for terms of use.
 */

#ifndef BRDREPLY_H
#define BRDREPLY_H

#include <QNetworkReply>

class BrdReply : public QNetworkReply
{
  Q_OBJECT
public:
  explicit BrdReply(const QByteArray &data, QObject *parent = 0);
  virtual void abort() override {}
  virtual qint64 bytesAvailable() const override;
  virtual qint64 readData(char *data, qint64 maxlen) override;
private:
  QByteArray _data;
  qint64 _offset;
};

#endif // BRDREPLY_H
