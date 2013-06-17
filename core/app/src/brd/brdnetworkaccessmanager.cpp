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
  if (request.url().scheme() == "brd" && op == GetOperation)
  {
    QByteArray data = _store->getObject(request.url().path());
    if (!data.isEmpty())
    {
      return new BrdReply(data, this);
    }
  }
  return QNetworkAccessManager::createRequest(op, request, outgoingData);
}
