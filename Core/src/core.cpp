/*
 * Copyright (C) 2012 Kulabuhov Michael, Kemerovo, Russia.
 *
 * See the LICENSE file for terms of use.
 */

#include <QDeclarativeContext>
#include <QApplication>
#include <QKeyEvent>
#include <QDir>
#include <QWidget>
#include "iplugin.h"
#include "core.h"

using namespace Qt;

Core::Core(QDeclarativeView *parent) :
  QObject(parent),
  menu_visible_(false),
  keyboard_(false),
  plugin_info_(NULL),
  loader_(NULL)
{
  loadPluginInfo();
  QDeclarativeContext *context = parent->rootContext();
  context->setContextProperty(QString("Core"), this);
  context->setContextProperty(QString("PluginInfoList"),
                              QVariant::fromValue(plugin_info_list_));
}

void Core::addPluginObject(const QString &name, QObject *obj)
{
  QDeclarativeView *view = qobject_cast<QDeclarativeView*>(parent());
  view->rootContext()->setContextProperty(name, obj);
}

void Core::addPluginWebObject(const QString &name, QObject *obj)
{
  emit addWebViewPluginObject(name, obj);
}

void Core::loadWebPage(const QString &url)
{
  emit loadWebViewPage(url);
}

QObject *Core::mainView()
{
  return parent();
}

void Core::emulateKeyPress(int key, int modifiers, const QString &text) const
{
  KeyboardModifiers md = KeyboardModifiers(modifiers);
  QKeyEvent *event = new QKeyEvent(QEvent::KeyPress, key, md, text);
  QApplication::postEvent(QApplication::focusWidget(), event);
}

void Core::selectPlugin(QObject *obj)
{
  PluginInfo *plugin_info = qobject_cast<PluginInfo*>(obj);
  if (!plugin_info) return;
  emit unloadPlugin(plugin_info_);
  delete loader_;
  loader_ = new QPluginLoader(plugin_info->libName(), this);
  QObject *plugin_obj = loader_->instance();
  if (!plugin_obj) return;
  IPlugin *plugin = qobject_cast<IPlugin*>(plugin_obj);
  if (!plugin) return;
  QDeclarativeView *view = qobject_cast<QDeclarativeView*>(parent());
  if (!view) return;
  plugin->init(this);
  plugin_info_ = plugin_info;
  emit loadPlugin(plugin_info);
  setMenuVisible(false);
}

void Core::loadPluginInfo()
{
  QDir dir = QDir(QApplication::applicationDirPath());
  if (!dir.cd("plugins")) return;
  QStringList filter("*.info");
  QFileInfoList files = dir.entryInfoList(filter, QDir::Files);
  foreach (QFileInfo file_info, files)
  {
    QPluginLoader *loader = new QPluginLoader(file_info.filePath(), this);
    QObject* obj = loader->instance();
    if (!obj) continue;
    IPluginInfo *iplugin_info = qobject_cast<IPluginInfo*>(obj);
    if (!iplugin_info) continue;
    QString lib_name = dir.filePath(file_info.completeBaseName().append(".plugin"));
    PluginInfo *plugin_info = new PluginInfo(iplugin_info, lib_name, this);
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
