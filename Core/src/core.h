/*
 * Copyright (C) 2012 Kulabuhov Michael, Kemerovo, Russia.
 *
 * See the LICENSE file for terms of use.
 */

#ifndef CORE_H
#define CORE_H

#include <QObject>
#include <QDeclarativeView>
#include <QList>
#include <QPluginLoader>
#include <QDir>
#include <QSettings>
#include "icore.h"
#include "iplugininfo.h"

class Core : public QObject, public ICore
{
  Q_OBJECT
  Q_INTERFACES(ICore)
  Q_PROPERTY(bool pluginMode READ pluginMode CONSTANT FINAL)
  Q_PROPERTY(bool menuVisible READ menuVisible WRITE setMenuVisible NOTIFY updateMenuVisible FINAL)
  Q_PROPERTY(QObjectList menuItemList READ menuItemList NOTIFY updateMenuItemList FINAL)
  Q_PROPERTY(bool isRootMenu READ isRootMenu NOTIFY updateMenuItemList FINAL)
  Q_PROPERTY(bool keyboard READ keyboard WRITE setKeyboard NOTIFY updateKeyboard FINAL)

public:
  explicit Core(QDeclarativeView *parent = 0);
  void addPlugin(const QString &name, const QString &image,
                         const QString &plugin_name = QString::null,
                         const QStringList &plugin_param = QStringList());
  void addObject(const QString &name, QObject *obj);
  void addQml(const QString &path);
  QObject *loadLib(const QString &lib_name);
  void loadLibs(const QStringList &libs);
  QObjectList libs() { return libs_; }
  QObject *getLib(const QString &name);
  QObject *mainView() { return parent(); }
  QDir rootDir() { return root_dir_; }
  QSettings *settings() { return settings_; }
  void showError(const QString &error);
  void init();
  bool pluginMode() { return plugin_mode_; }
  bool menuVisible() { return menu_visible_; }
  QObjectList menuItemList() { return menu_item_list_; }
  bool isRootMenu() { return menu_path_.isEmpty(); }
  bool keyboard() { return keyboard_; }

signals:
  void updatePluginInfo();
  void updateMenuVisible();
  void updateMenuItemList();
  void updateKeyboard();
  void loadPlugin();
  void unloadPlugin();
  void addPluginQml(QString path);

public slots:
  void setMenuVisible(bool menu_visible);
  void setKeyboard(bool keyboard);
  void emulateKeyPress(int key, int modifiers, const QString & text = "") const;
  void selectMenuItem(QObject *obj);
  void upMenu();
  void quitButton();
  void minimizeButton();

private:
  bool plugin_mode_;
  bool menu_visible_;
  bool keyboard_;
  QList<IPluginInfo*> plugin_info_list_;
  QObjectList libs_;
  QString menu_path_;
  QObjectList menu_item_list_;
  QPluginLoader *loader_;
  QDir root_dir_;
  QSettings *settings_;

  void loadPluginInfo();
  void updateMenu();
  void unloadPluginInternal();
  bool loadPluginInternal(const QString &plugin_name, const QStringList &param);
};

#endif // CORE_H
