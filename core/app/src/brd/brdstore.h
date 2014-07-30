/*
 * Copyright (C) 2013 Michael Kulabuhov, Kemerovo, Russia.
 *
 * See the LICENSE file for terms of use.
 */

#ifndef BRDSTORE_H
#define BRDSTORE_H

#include <QMap>
#include <QSet>
#include <QSharedPointer>
#include <QObject>
#include "ibrdstore.h"

class BrdStore : public QObject, public IBrdStore
{
  Q_OBJECT
  Q_INTERFACES(IBrdStore)
public:
  explicit BrdStore(QObject *parent = 0);

  // IBrdStore
  virtual QString addObject(const QByteArray &data) override;
  virtual QString addFromFile(const QString &file_name) override;
  virtual QString addFromUrl(const QUrl &url) override;
  virtual QByteArray getObject(const QString &hash) override;
  virtual QString getUrlString(const QString &hash) override;
  virtual int addTempObject(const QByteArray &data) override;
  virtual void removeTempObject(int id) override;
  virtual QByteArray getTempObject(int id) override;
  virtual QString getTempUrl(int id) override;

  void clear();
private:
  class BrdObject;
  QMap<QString, QSharedPointer<BrdObject>> _store;
  QMap<int, QByteArray> _tmp_store;
  QSet<int> _tmp_free;
  QSet<int> _tmp_used;
  int _tmp_next;
};

#endif // BRDSTORE_H
