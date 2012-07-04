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
#include "icore.h"
#include "plugininfo.h"

class Core : public QObject, public ICore
{
  Q_OBJECT
  Q_INTERFACES(ICore)
  Q_PROPERTY(bool menuVisible READ menuVisible WRITE setMenuVisible NOTIFY updateMenuVisible)
  Q_PROPERTY(bool keyboard READ keyboard WRITE setKeyboard NOTIFY updateKeyboard)

public:
  explicit Core(QDeclarativeView *parent = 0);
  virtual void addPlugin(const QString &full_name, const QString &image,
                         const QString &plugin_name = QString(),
                         const QStringList &plugin_param = QStringList());
  virtual void addObject(const QString &name, QObject *obj);
  virtual void addPluginWebObject(const QString &name, QObject *obj);
  virtual void loadWebPage(const QString &url);
  virtual QObject *mainView();
  bool menuVisible() { return menu_visible_; }
  bool keyboard() { return keyboard_; }

signals:
  void updateMenuVisible();
  void updateKeyboard();
  void loadPlugin(QObject *plugin);
  void unloadPlugin(QObject *plugin);
  void addWebViewPluginObject(QString name, QObject *obj);
  void loadWebViewPage(QString url);

public slots:
  void setMenuVisible(bool menu_visible);
  void setKeyboard(bool keyboard);
  void emulateKeyPress(int key, int modifiers, const QString & text = "") const;
  void selectPlugin(QObject *obj);

private:
  bool menu_visible_;
  bool keyboard_;
  PluginInfo *root_plugin_info_;
  PluginInfo *plugin_info_;
  QPluginLoader *loader_;

  void loadPluginInfo();
};

#endif // CORE_H
