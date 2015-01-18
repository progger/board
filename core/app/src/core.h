/*
 * Copyright (C) 2012 Michael Kulabuhov, Kemerovo, Russia.
 *
 * See the LICENSE file for terms of use.
 */

#ifndef CORE_H
#define CORE_H

#include <QMap>
#include <QQmlEngine>
#include <QQuickWindow>
#include <QDir>
#include <QSettings>
#include <QQmlListProperty>
#include <quazip/quazip.h>
#include "icore.h"
#include "iplugin.h"
#include "paint/sheet.h"
#include "panel/panel.h"
#include "panel/tool.h"

class BrdStore;
class Paint;
class Style;

class Core : public QObject, public ICore
{
  Q_OBJECT
  Q_INTERFACES(ICore)
  Q_PROPERTY(bool windowMode READ windowMode CONSTANT)
  Q_PROPERTY(bool keyboard READ keyboard WRITE setKeyboard NOTIFY keyboardChanged FINAL)
  Q_PROPERTY(bool transparent READ transparent WRITE setTransparent NOTIFY transparentChanged FINAL)
  Q_PROPERTY(bool hasChanges READ hasChanges NOTIFY hasChangesChanged FINAL)
  Q_PROPERTY(int sheetIndex READ sheetIndex WRITE setSheetIndex NOTIFY sheetIndexChanged FINAL)
  Q_PROPERTY(Paint paint READ paintObj CONSTANT FINAL)
  Q_PROPERTY(QQmlListProperty<Sheet> sheets READ sheetsProperty NOTIFY sheetsChanged FINAL)
public:
  explicit Core(QQmlEngine *engine);

  // ICore
  virtual QWindow *mainWindow() override;
  virtual QDir rootDir() override;
  virtual QSettings *settings() override;
  virtual IPaint *paint() override;
  virtual IBrdStore *brdStore() override;
  virtual int sheetsCount() override;
  virtual int sheetIndex() override;
  virtual ISheet *sheet(int index) override;
  virtual QQmlComponent *getComponent(const QString &url_string) override;
  virtual void logMessage(const QString &message) override;
  virtual void logError(const QString &error) override;
  virtual void showError(const QString &error) override;
  virtual void registerTool(const QString &name, const QString &section, const QString &url_string) override;
  virtual void setChanges() override;
  virtual bool hasChanges() override;

  void init(QWindow *main_window);
  bool windowMode() const;
  bool keyboard() const { return _keyboard; }
  bool transparent() const { return _transparent; }
  Paint *paintObj() const { return _paint; }
  QList<Sheet*> sheets() const { return _sheets; }
  QQmlListProperty<Sheet> sheetsProperty();
signals:
  void keyboardChanged();
  void transparentChanged();
  void sheetIndexChanged();
  void sheetsChanged();
  void hasChangesChanged();
  void errorMessageBox(const QString &error);
public slots:
  void setKeyboard(bool keyboard);
  void setTransparent(bool transparent);
  void setSheetIndex(int index);
  void emulateKeyPress(int key, int modifiers, const QString & text = "") const;
  void quitButton();
  void minimizeButton();
  void saveBook(const QUrl &file_url);
  void openBook(const QUrl &file_url);
  void insertSheet(int index);
  void deleteSheet(int index);
  void quitActions();
private:
  QQmlEngine *_engine;
  QWindow *_main_window;
  bool _keyboard;
  bool _transparent;
  int _sheet_index;
  QDir _root_dir;
  QSettings *_settings;
  BrdStore *_brdStore;
  Paint *_paint;
  QMap<QString, QQmlComponent*> _map_componenet;
  QQmlComponent *_comp_sheet;
  QQmlComponent *_comp_panel;
  QQuickItem *_panel_place;
  QQuickItem *_sheet_place;
  QList<Panel*> _panels;
  QMap<QString, Tool*> _tools;
  QList<Sheet*> _sheets;
  QList<IPlugin*> _plugins;
  bool _changes;
  Sheet *createSheet();
  void saveBookFiles(QuaZip *zip);
  void openBookFiles(QuaZip *zip);
  void loadPlugins();
  void initPlugins();
  void savePanels();
  void loadPanels();
};

#endif // CORE_H
