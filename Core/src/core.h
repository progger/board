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
#include "plugininfo.h"

class Core : public QObject, public ICore
{
  Q_OBJECT
  Q_INTERFACES(ICore)
  Q_PROPERTY(bool pluginMode READ pluginMode)
  Q_PROPERTY(bool menuVisible READ menuVisible WRITE setMenuVisible NOTIFY updateMenuVisible)
  Q_PROPERTY(bool keyboard READ keyboard WRITE setKeyboard NOTIFY updateKeyboard)

public:
  explicit Core(QDeclarativeView *parent = 0);
  virtual void addPlugin(const QString &full_name, const QString &image,
                         const QString &plugin_name = QString(),
                         const QStringList &plugin_param = QStringList());
  virtual void addObject(const QString &name, QObject *obj);
  virtual void addQml(const QString &path);
  virtual void loadLib(const QString &lib_name);
  virtual void loadLibs(const QStringList &libs);
  virtual QObjectList libs() { return libs_; }
  virtual QObject *getLib(const QString &name);
  virtual QObject *mainView() { return parent(); }
  virtual QDir rootDir() { return root_dir_; }
  virtual QSettings *settings() { return settings_; }
  void init();
  bool pluginMode() { return plugin_mode_; }
  bool menuVisible() { return menu_visible_; }
  bool keyboard() { return keyboard_; }

signals:
  void updatePluginInfo();
  void updateMenuVisible();
  void updateKeyboard();
  void loadPlugin();
  void unloadPlugin();
  void addPluginQml(QString path);

public slots:
  void setMenuVisible(bool menu_visible);
  void setKeyboard(bool keyboard);
  void emulateKeyPress(int key, int modifiers, const QString & text = "") const;
  void selectPlugin(QObject *obj);

private:
  bool plugin_mode_;
  bool menu_visible_;
  bool keyboard_;
  QObjectList libs_;
  PluginInfo *root_plugin_info_;
  PluginInfo *plugin_info_;
  QPluginLoader *loader_;
  QDir root_dir_;
  QSettings *settings_;

  void loadPluginInfo();
  void unloadPluginInternal();
  bool loadPluginInternal(const QString &plugin_name, const QStringList &param);
};

#endif // CORE_H
