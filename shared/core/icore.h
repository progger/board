/*
 * Copyright (C) 2012 Michael Kulabuhov, Kemerovo, Russia.
 *
 * See the LICENSE file for terms of use.
 */

#ifndef ICORE_H
#define ICORE_H

#include <QWindow>
#include <QQmlComponent>
#include <QDir>
#include <QSettings>
#include "ipaint.h"
#include "isheet.h"
#include "ibrdstore.h"

using ImportFunc = bool (*)(const QString &);
using ExportFunc = void (*)(const QString &);

class ICore {
  Q_DISABLE_COPY_MOVE(ICore)
public:
  ICore() = default;
  virtual ~ICore() = default;
  virtual QWindow *mainWindow() = 0;
  virtual QDir rootDir() = 0;
  virtual QSettings *settings() = 0;
  virtual IPaint *paint() = 0;
  virtual IBrdStore *brdStore() = 0;
  virtual int sheetsCount() = 0;
  virtual int sheetIndex() = 0;
  virtual ISheet *sheet(int index) = 0;
  virtual QQmlComponent *getComponent(const QString &url_string) = 0;
  virtual bool hasChanges() = 0;
public slots:
  virtual void logMessage(const QString &message) = 0;
  virtual void logError(const QString &error) = 0;
  virtual void showError(const QString &error) = 0;
  virtual void registerTool(const QString &name, const QString &section, QQmlComponent *component, int width, int height) = 0;
  virtual void registerImporter(const QString &name, const QString &suffix, ImportFunc func) = 0;
  virtual void registerExporter(const QString &name, const QString &suffix, ExportFunc func) = 0;
  virtual ISheet *addSheet() = 0;
  virtual ISheet *insertSheet(int index) = 0;
  virtual void deleteSheet(int index) = 0;
  virtual void setChanges() = 0;
signals:
  virtual void sheetsChanged() = 0;
  virtual void sheetIndexChanged() = 0;
  virtual void hasChangesChanged() = 0;
};

Q_DECLARE_INTERFACE(ICore, "board.core.ICore")

#endif // ICORE_H
