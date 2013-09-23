/*
 * Copyright (C) 2012 Michael Kulabuhov, Kemerovo, Russia.
 *
 * See the LICENSE file for terms of use.
 */

#ifndef ICORE_H
#define ICORE_H

#include <QQmlComponent>
#include <QDir>
#include <QSettings>
#include "ipaint.h"
#include "isheet.h"
#include "ibrdstore.h"

class ICore {
public:
  virtual ~ICore() {}
  virtual QObject *mainView() = 0;
  virtual QDir rootDir() = 0;
  virtual QSettings *settings() = 0;
  virtual IPaint *paint() = 0;
  virtual IBrdStore *brdStore() = 0;
  virtual int sheetsCount() = 0;
  virtual int sheetIndex() = 0;
  virtual ISheet *sheet(int index) = 0;
  virtual QQmlComponent *getComponent(const QString &url_string) = 0;
  virtual void logMessage(const QString &message) = 0;
  virtual void logError(const QString &error) = 0;
  virtual void showError(const QString &error) = 0;
  virtual void addPluginRowItem(const QString &url_string) = 0;
  virtual void setChanges() = 0;
};

Q_DECLARE_INTERFACE(ICore, "board.core.ICore/2.1")

#endif // ICORE_H
