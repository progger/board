/*
 * Copyright (C) 2012 Michael Kulabuhov, Kemerovo, Russia.
 *
 * See the LICENSE file for terms of use.
 */

#ifndef IBRDSTORE_H
#define IBRDSTORE_H

#include <QObject>
#include <QUrl>

class IBrdStore {
  Q_DISABLE_COPY_MOVE(IBrdStore)
public:
  IBrdStore() = default;
  virtual ~IBrdStore() = default;
  virtual QString addObject(const QByteArray &data) = 0;
  virtual QString addFromFile(const QString &file_name) = 0;
  virtual QString addFromUrl(const QUrl &url) = 0;
  virtual QByteArray getObject(const QString &hash) = 0;
  virtual QString getUrlString(const QString &hash) = 0;
  virtual int addTempObject(const QByteArray &data) = 0;
  virtual void removeTempObject(int id) = 0;
  virtual QByteArray getTempObject(int id) = 0;
  virtual QString getTempUrl(int id) = 0;
};

Q_DECLARE_INTERFACE(IBrdStore, "board.core.IBrdStore")

#endif // IBRDSTORE_H
