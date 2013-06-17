/*
 * Copyright (C) 2012 Michael Kulabuhov, Kemerovo, Russia.
 *
 * See the LICENSE file for terms of use.
 */

#ifndef IBRDSTORE_H
#define IBRDSTORE_H

#include <QString>

class IBrdStore {
public:
  virtual ~IBrdStore() {}
  virtual QString addObject(const QByteArray &data) = 0;
  virtual QString addFromFile(const QString &file_name) = 0;
  virtual QByteArray getObject(const QString &hash) = 0;
  virtual QString getUrlString(const QString &hash) = 0;
};

Q_DECLARE_INTERFACE(IBrdStore, "board.core.IBrdStore/2.0")

#endif // IBRDSTORE_H
