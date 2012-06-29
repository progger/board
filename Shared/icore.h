/*
 * Copyright (C) 2012 Kulabuhov Michael, Kemerovo, Russia.
 *
 * See the LICENSE file for terms of use.
 */

#ifndef ICORE_H
#define ICORE_H

#include <QObject>

class ICore {
public:
  virtual ~ICore() {}
  virtual void addPluginObject(const QString &name, QObject *obj) = 0;
  virtual void addPluginWebObject(const QString &name, QObject *obj) = 0;
  virtual void loadWebPage(const QString &url) = 0;
  virtual QObject *mainView() = 0;
};

Q_DECLARE_INTERFACE(ICore, "Board.ICore/1.0")

#endif // ICORE_H
