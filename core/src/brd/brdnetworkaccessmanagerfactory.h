/*
 * Copyright (C) 2013 Kulabuhov Michael, Kemerovo, Russia.
 *
 * See the LICENSE file for terms of use.
 */

#ifndef BRDNETWORKACCESSMANAGERFACTORY_H
#define BRDNETWORKACCESSMANAGERFACTORY_H

#include <QQmlNetworkAccessManagerFactory>

class BrdStore;

class BrdNetworkAccessManagerFactory : public QQmlNetworkAccessManagerFactory
{
public:
  explicit BrdNetworkAccessManagerFactory(BrdStore *store);
  virtual QNetworkAccessManager *create(QObject *parent) override;
private:
  BrdStore *_store;
};

#endif // BRDNETWORKACCESSMANAGERFACTORY_H
