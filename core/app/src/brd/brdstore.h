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

class BrdStore final : public QObject, public IBrdStore
{
  Q_OBJECT
  Q_INTERFACES(IBrdStore)
  Q_DISABLE_COPY_MOVE(BrdStore)
public:
  explicit BrdStore(QObject *parent = nullptr);
  ~BrdStore() override = default;

  // IBrdStore
  QString addObject(const QByteArray &data) override;
  QString addFromFile(const QString &file_name) override;
  QString addFromUrl(const QUrl &url) override;
  QByteArray getObject(const QString &hash) override;
  QString getUrlString(const QString &hash) override;
  int addTempObject(const QByteArray &data) override;
  void removeTempObject(int id) override;
  QByteArray getTempObject(int id) override;
  QString getTempUrl(int id) override;

  void clear();
private:
  QMap<QString, QByteArray> _store;
  QMap<int, QByteArray> _tmp_store;
  QSet<int> _tmp_free;
  QSet<int> _tmp_used;
  int _tmp_next;
};

#endif // BRDSTORE_H
