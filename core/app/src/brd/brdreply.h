/*
 * Copyright (C) 2013 Kulabuhov Michael, Kemerovo, Russia.
 *
 * See the LICENSE file for terms of use.
 */

#ifndef BRDREPLY_H
#define BRDREPLY_H

#include <memory>
#include <QNetworkReply>

struct BrdObject;

class BrdReply : public QNetworkReply
{
  Q_OBJECT
public:
  explicit BrdReply(std::shared_ptr<BrdObject> object, QObject *parent = 0);
  virtual void abort() override {}
  virtual qint64 bytesAvailable() const override;
  virtual qint64 readData(char *data, qint64 maxlen) override;
private:
  std::shared_ptr<BrdObject> _object;
  qint64 _offset;
};

#endif // BRDREPLY_H
