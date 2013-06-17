/*
 * Copyright (C) 2013 Michael Kulabuhov, Kemerovo, Russia.
 *
 * See the LICENSE file for terms of use.
 */

#include "brdnetworkaccessmanager.h"
#include "brdnetworkaccessmanagerfactory.h"

BrdNetworkAccessManagerFactory::BrdNetworkAccessManagerFactory(BrdStore *store, QObject *parent) :
  QObject(parent),
  _store(store)
{
}

QNetworkAccessManager *BrdNetworkAccessManagerFactory::create(QObject *parent)
{
  return new BrdNetworkAccessManager(_store, parent);
}
