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
#include "importer.h"
#include "exporter.h"

class BrdStore;
class Paint;
class Style;

class Core : public QObject, public ICore
{
  Q_OBJECT
  Q_INTERFACES(ICore)
  Q_PROPERTY(bool windowMode READ windowMode CONSTANT)
  Q_PROPERTY(bool keyboard READ keyboard WRITE setKeyboard NOTIFY keyboardChanged)
  Q_PROPERTY(bool transparent READ transparent WRITE setTransparent NOTIFY transparentChanged)
  Q_PROPERTY(bool hasChanges READ hasChanges NOTIFY hasChangesChanged)
  Q_PROPERTY(int sheetIndex READ sheetIndex WRITE setSheetIndex NOTIFY sheetIndexChanged)
  Q_PROPERTY(Paint paint READ paintObj CONSTANT)
  Q_PROPERTY(QQmlListProperty<Sheet> sheets READ sheetsProperty NOTIFY sheetsChanged)
  Q_PROPERTY(QQmlListProperty<ToolInfo> tools READ toolsProperty NOTIFY toolsChanged)
  Q_PROPERTY(QQmlListProperty<Panel> panels READ panelsProperty NOTIFY panelsChanged)
  Q_PROPERTY(QQmlListProperty<Importer> importers READ importersProperty NOTIFY importersChanged)
  Q_PROPERTY(QQmlListProperty<Exporter> exporters READ exportersProperty NOTIFY exportersChanged)
public:
  explicit Core(QQmlEngine *engine, bool window_mode);

  // ICore
public:
  virtual QWindow *mainWindow() override;
  virtual QDir rootDir() override;
  virtual QSettings *settings() override;
  virtual IPaint *paint() override;
  virtual IBrdStore *brdStore() override;
  virtual int sheetsCount() override;
  virtual int sheetIndex() override;
  virtual ISheet *sheet(int index) override;
  virtual QQmlComponent *getComponent(const QString &url_string) override;
  virtual bool hasChanges() override;
public slots:
  virtual void logMessage(const QString &message) override;
  virtual void logError(const QString &error) override;
  virtual void showError(const QString &error) override;
  virtual void registerTool(const QString &name, const QString &section, QQmlComponent *component, int width, int height) override;
  virtual void registerImporter(const QString &name, const QString &suffix, ImportFunc func) override;
  virtual void registerExporter(const QString &name, const QString &suffix, ExportFunc func) override;
  virtual ISheet *addSheet() override;
  virtual ISheet *insertSheet(int index) override;
  virtual void deleteSheet(int index) override;
  virtual void setChanges() override;
signals:
  void sheetsChanged();
  void sheetIndexChanged();
  void hasChangesChanged();

public:
  void init(QWindow *main_window, const QString &brd_file);
  bool windowMode() const;
  bool keyboard() const { return _keyboard; }
  bool transparent() const { return _transparent; }
  Paint *paintObj() const { return _paint; }
  QList<Sheet*> sheets() const { return _sheets; }
  QQmlListProperty<Sheet> sheetsProperty();
  QList<ToolInfo*> tools() const;
  QQmlListProperty<ToolInfo> toolsProperty();
  QList<Panel*> panels() const { return _panels; }
  QQmlListProperty<Panel> panelsProperty();
  QList<Importer*> importers() const { return _importers; }
  QQmlListProperty<Importer> importersProperty();
  QList<Exporter*> exporters() const { return _exporters; }
  QQmlListProperty<Exporter> exportersProperty();
public slots:
  void setKeyboard(bool keyboard);
  void setTransparent(bool transparent);
  void setSheetIndex(int index);
  void emulateKeyPress(int key, int modifiers, const QString & text = "") const;
  void quitButton();
  void minimizeButton();
  void newBook();
  void saveBook(const QUrl &file_url);
  void openBook(const QUrl &file_url);
  void quitActions();
signals:
  void keyboardChanged();
  void transparentChanged();
  void toolsChanged();
  void panelsChanged();
  void importersChanged();
  void exportersChanged();
  void errorMessageBox(const QString &error);
private:
  QQmlEngine *_engine;
  QWindow *_main_window;
  bool _window_mode;
  bool _keyboard;
  bool _transparent;
  int _sheet_index;
  QDir _root_dir;
  QSettings *_settings;
  BrdStore *_brdStore;
  Paint *_paint;
  QMap<QString, QQmlComponent*> _map_componenet;
  QQmlComponent *_comp_sheet;
  QQuickItem *_sheet_place;
  QList<Panel*> _panels;
  QMap<QString, ToolInfo*> _tools;
  QList<Sheet*> _sheets;
  QList<IPlugin*> _plugins;
  QList<Importer*> _importers;
  QList<Exporter*> _exporters;
  bool _changes;
  Sheet* createSheet();
  void clearBook();
  void loadPlugins();
  void initPlugins();
  void savePanels();
  void loadPanels();
};

#endif // CORE_H
