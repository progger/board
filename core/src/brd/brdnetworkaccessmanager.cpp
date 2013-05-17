/*
 * Copyright (C) 2013 Kulabuhov Michael, Kemerovo, Russia.
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
    auto object = _store->getObject(request.url().path());
    if (object)
    {
      return new BrdReply(object, this);
    }
  }
  return QNetworkAccessManager::createRequest(op, request, outgoingData);
}
