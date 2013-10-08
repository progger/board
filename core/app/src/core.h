/*
 * Copyright (C) 2012 Michael Kulabuhov, Kemerovo, Russia.
 *
 * See the LICENSE file for terms of use.
 */

#ifndef CORE_H
#define CORE_H

#include <vector>
#include <map>
#include <QQmlEngine>
#include <QQuickWindow>
#include <QDir>
#include <QSettings>
#include <QQmlListProperty>
#include "quazip.h"
#include "icore.h"
#include "iplugin.h"
#include "paint/sheet.h"

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
  Q_PROPERTY(QQmlListProperty<QQuickItem> sheets READ sheetsProperty NOTIFY sheetsChanged FINAL)
public:
  explicit Core(QQmlEngine *engine);

  // ICore
  virtual QObject *mainView() override;
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
  virtual void addPluginRowItem(const QString &url_string) override;
  virtual void setChanges() override;
  virtual bool hasChanges() override;

  void init(QQuickWindow *main_window);
  bool windowMode() const;
  bool keyboard() const { return _keyboard; }
  bool transparent() const { return _transparent; }
  Paint *paintObj() const { return _paint; }
  std::vector<Sheet*> *sheets() { return &_sheets; }
  QQmlListProperty<QQuickItem> sheetsProperty();
signals:
  void keyboardChanged();
  void transparentChanged();
  void sheetIndexChanged();
  void sheetsChanged();
  void hasChangesChanged();
public slots:
  void setKeyboard(bool keyboard);
  void setTransparent(bool transparent);
  void setSheetIndex(int index);
  void emulateKeyPress(int key, int modifiers, const QString & text = "") const;
  void quitButton();
  void minimizeButton();
  void saveBook();
  void saveBook(const QString &file_name);
  void openBook();
  void openBook(const QString &file_name);
  void insertSheet(int index);
  void deleteSheet(int index);
private:
  QQmlEngine *_engine;
  QQuickWindow *_main_window;
  bool _keyboard;
  bool _transparent;
  int _sheet_index;
  QDir _root_dir;
  QSettings *_settings;
  BrdStore *_brdStore;
  Paint *_paint;
  std::map<QString, QQmlComponent*> _map_componenet;
  QQmlComponent *_comp_sheet;
  QQuickItem *_sheet_place;
  QQuickItem *_plugin_row;
  std::vector<Sheet*> _sheets;
  std::vector<IPlugin*> _plugins;
  bool _changes;
  Sheet *createSheet();
  void saveBookFiles(QuaZip *zip);
  void openBookFiles(QuaZip *zip);
  void loadPlugins();
  void initPlugins();
};

#endif // CORE_H
