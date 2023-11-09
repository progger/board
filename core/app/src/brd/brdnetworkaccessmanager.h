/*
 * Copyright (C) 2013 Michael Kulabuhov, Kemerovo, Russia.
 *
 * See the LICENSE file for terms of use.
 */

#ifndef BRDNETWORKACCESSMANAGER_H
#define BRDNETWORKACCESSMANAGER_H

#include <QNetworkAccessManager>

class BrdStore;

class BrdNetworkAccessManager : public QNetworkAccessManager
{
  Q_OBJECT
  Q_DISABLE_COPY_MOVE(BrdNetworkAccessManager)
public:
  explicit BrdNetworkAccessManager(BrdStore *store, QObject *parent = nullptr);
  ~BrdNetworkAccessManager() override = default;
protected:
  QNetworkReply *createRequest(Operation op, const QNetworkRequest &request, QIODevice *outgoingData) override;
private:
  BrdStore *_store;
};

#endif // BRDNETWORKACCESSMANAGER_H
