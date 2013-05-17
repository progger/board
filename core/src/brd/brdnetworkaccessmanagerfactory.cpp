/*
 * Copyright (C) 2013 Kulabuhov Michael, Kemerovo, Russia.
 *
 * See the LICENSE file for terms of use.
 */

#include "brdnetworkaccessmanager.h"
#include "brdnetworkaccessmanagerfactory.h"

BrdNetworkAccessManagerFactory::BrdNetworkAccessManagerFactory(BrdStore *store) :
  _store(store)
{
}

QNetworkAccessManager *BrdNetworkAccessManagerFactory::create(QObject *parent)
{
  return new BrdNetworkAccessManager(_store, parent);
}
