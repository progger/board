/*
 * Copyright (C) 2013 Michael Kulabuhov, Kemerovo, Russia.
 *
 * See the LICENSE file for terms of use.
 */

#include <QNetworkRequest>
#include "brdstore.h"
#include "brdreply.h"
#include "brdnetworkaccessmanager.h"

BrdNetworkAccessManager::BrdNetworkAccessManager(BrdStore *store, QObject *parent) :
  QNetworkAccessManager(parent),
  _store(store)
{
}

QNetworkReply *BrdNetworkAccessManager::createRequest(QNetworkAccessManager::Operation op, const QNetworkRequest &request, QIODevice *outgoingData)
{
  if (op == GetOperation)
  {
    QString scheme = request.url().scheme();
    if (scheme == "brd")
    {
      QByteArray data = _store->getObject(request.url().path());
      if (!data.isEmpty())
      {
        return new BrdReply(data, this);
      }
    }
    if (scheme == "tmp")
    {
      QByteArray data = _store->getTempObject(request.url().path().toInt());
      if (!data.isEmpty())
      {
        return new BrdReply(data, this);
      }
    }
  }
  return QNetworkAccessManager::createRequest(op, request, outgoingData);
}
