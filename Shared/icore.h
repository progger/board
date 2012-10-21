/*
 * Copyright (C) 2012 Kulabuhov Michael, Kemerovo, Russia.
 *
 * See the LICENSE file for terms of use.
 */

#ifndef ICORE_H
#define ICORE_H

#include <QObject>
#include <QStringList>

class ICore {
public:
  virtual ~ICore() {}
  virtual void addPlugin(const QString &full_name, const QString &image,
                         const QString &plugin_name = QString(),
                         const QStringList &plugin_param = QStringList()) = 0;
  virtual void addObject(const QString &name, QObject *obj) = 0;
  virtual void addQml(const QString &path) = 0;
  virtual void loadLib(const QString &lib_name) = 0;
  virtual void loadLibs(const QStringList &libs) = 0;
  virtual QObjectList libs() = 0;
  virtual QObject *getLib(const QString &name) = 0;
  virtual QObject *mainView() = 0;
};

Q_DECLARE_INTERFACE(ICore, "Board.ICore/1.0")

#endif // ICORE_H
