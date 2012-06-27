/*
 * Copyright (C) 2012 Kulabuhov Michael, Kemerovo, Russia.
 *
 * See the LICENSE file for terms of use.
 */

#ifndef CORE_H
#define CORE_H

#include <QObject>
#include <QList>
#include "plugininfo.h"

class Core : public QObject
{
  Q_OBJECT
  Q_PROPERTY(bool menuVisible READ menuVisible WRITE setMenuVisible NOTIFY updateMenuVisible)
  Q_PROPERTY(bool keyboard READ keyboard WRITE setKeyboard NOTIFY updateKeyboard)

public:
  explicit Core(QObject *parent = 0);
  QObjectList pluginInfoList() { return plugin_info_list_; }
  bool menuVisible() { return menu_visible_; }
  bool keyboard() { return keyboard_; }

signals:
  void updateMenuVisible();
  void updateKeyboard();

public slots:
  void setMenuVisible(bool menu_visible);
  void setKeyboard(bool keyboard);
  void emulateKeyPress(int key, int modifiers, const QString & text = "") const;

private:
  bool menu_visible_;
  bool keyboard_;
  QObjectList plugin_info_list_;

  void loadPluginInfo();
};

#endif // CORE_H
