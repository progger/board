/*
 * Copyright (C) 2012 Kulabuhov Michael, Kemerovo, Russia.
 *
 * See the LICENSE file for terms of use.
 */

#ifndef ICORE_H
#define ICORE_H

#include <QObject>
#include <QStringList>
#include <QDir>
#include <QSettings>

class ICore {
public:
  virtual ~ICore() {}
  virtual QObject *mainView() = 0;
  virtual QDir rootDir() = 0;
  virtual QSettings *settings() = 0;
  virtual void showError(const QString &error) = 0;
};

Q_DECLARE_INTERFACE(ICore, "board.ICore/2.0")

#endif // ICORE_H
