/*
 * Copyright (C) 2012 Kulabuhov Michael, Kemerovo, Russia.
 *
 * See the LICENSE file for terms of use.
 */

#include <QApplication>
#include <QKeyEvent>
#include <QDir>
#include <QPluginLoader>
#include "iplugininfo.h"
#include "core.h"
#include "mainview.h"

using namespace Qt;

Core::Core(QObject *parent) :
  QObject(parent),
  menu_visible_(false),
  keyboard_(false)
{
  loadPluginInfo();
}

void Core::emulateKeyPress(int key, int modifiers, const QString &text) const
{
  KeyboardModifiers md = KeyboardModifiers(modifiers);
  QKeyEvent *event = new QKeyEvent(QEvent::KeyPress, key, md, text);
  QApplication::postEvent(QApplication::focusWidget(), event);
}

void Core::loadPluginInfo()
{
  QDir dir = QDir(QApplication::applicationDirPath());
  if (!dir.cd("plugins")) return;
  QStringList filter("*_info.*");
  QFileInfoList files = dir.entryInfoList(filter, QDir::Files);
  foreach (QFileInfo file_info, files)
  {
    QPluginLoader *loader = new QPluginLoader(file_info.filePath(), this);
    QObject* obj = loader->instance();
    if (!obj) continue;
    IPluginInfo *iplugin_info = qobject_cast<IPluginInfo*>(obj);
    if (!iplugin_info) continue;
    PluginInfo *plugin_info = new PluginInfo(iplugin_info, this);
    plugin_info_list_.append(plugin_info);
  }
}

void Core::setKeyboard(bool keyboard)
{
  keyboard_ = keyboard;
  emit updateKeyboard();
}

void Core::setMenuVisible(bool menu_visible)
{
  menu_visible_ = menu_visible;
  emit updateMenuVisible();
}
