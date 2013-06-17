/*
 * Copyright (C) 2013 Michael Kulabuhov, Kemerovo, Russia.
 *
 * See the LICENSE file for terms of use.
 */

#ifndef BRDNETWORKACCESSMANAGERFACTORY_H
#define BRDNETWORKACCESSMANAGERFACTORY_H

#include <QQmlNetworkAccessManagerFactory>

class BrdStore;

class BrdNetworkAccessManagerFactory : public QObject, public QQmlNetworkAccessManagerFactory
{
  Q_OBJECT
public:
  explicit BrdNetworkAccessManagerFactory(BrdStore *store, QObject *parent);
  virtual QNetworkAccessManager *create(QObject *parent) override;
private:
  BrdStore *_store;
};

#endif // BRDNETWORKACCESSMANAGERFACTORY_H
