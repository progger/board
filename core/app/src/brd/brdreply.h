/*
 * Copyright (C) 2013 Michael Kulabuhov, Kemerovo, Russia.
 *
 * See the LICENSE file for terms of use.
 */

#ifndef BRDREPLY_H
#define BRDREPLY_H

#include <QNetworkReply>

class BrdReply : public QNetworkReply
{
  Q_OBJECT
  Q_DISABLE_COPY_MOVE(BrdReply)
public:
  explicit BrdReply(const QByteArray &data, QObject *parent = nullptr);
  ~BrdReply() override = default;
  void abort() override {}
  qint64 bytesAvailable() const override;
  qint64 readData(char *data, qint64 maxlen) override;
private:
  QByteArray _data;
  qint64 _offset;
};

#endif // BRDREPLY_H
