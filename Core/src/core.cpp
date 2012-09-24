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
#include "iexternal.h"
#include "iplugin.h"
#include "core.h"

using namespace Qt;

Core::Core(QDeclarativeView *parent) :
  QObject(parent),
  menu_visible_(true),
  keyboard_(false),
  plugin_info_(NULL)
{
  root_plugin_info_ = new PluginInfo(this, QString());
  loadPluginInfo();
  QDeclarativeContext *context = parent->rootContext();
  context->setContextProperty("Core", this);
  context->setContextProperty("RootPluginInfo", root_plugin_info_);
}

void Core::addPlugin(const QString &full_name, const QString &image,
                     const QString &plugin_name, const QStringList &plugin_param)
{
  QStringList path = full_name.split('/');
  PluginInfo *parent = root_plugin_info_;
  PluginInfo *plugin_info = NULL;
  foreach (QString name, path)
  {
    plugin_info = parent->findChild<PluginInfo *>(name);
    if (!plugin_info)
    {
      plugin_info = new PluginInfo(parent, name);
    }
    parent = plugin_info;
  }
  if (!plugin_info) return;
  if (!image.isEmpty())
    plugin_info->setImage(image);
  if (!plugin_name.isEmpty())
    plugin_info->setPluginName(plugin_name);
  if (!plugin_param.isEmpty())
    plugin_info->setPluginParam(plugin_param);
}

void Core::addObject(const QString &name, QObject *obj)
{
  QDeclarativeView *view = qobject_cast<QDeclarativeView*>(parent());
  if (!view) return;
  view->rootContext()->setContextProperty(name, obj);
}

void Core::addQml(const QString &path)
{
  emit addPluginQml(path);
}

void Core::addWebObject(const QString &name, QObject *obj)
{
  emit addPluginWebObject(name, obj);
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
  QDir dir = QDir(QApplication::applicationDirPath());
  if (!dir.cd("plugins")) return;
  QString file_name = plugin_info->pluginName() + ".plugin";
  if (!dir.exists(file_name)) return;
  file_name = dir.filePath(file_name);
  loader_ = new QPluginLoader(file_name, this);
  QObject *plugin_obj = loader_->instance();
  if (!plugin_obj) return;
  IPlugin *plugin = qobject_cast<IPlugin*>(plugin_obj);
  if (!plugin) return;
  plugin->init(this, plugin_info->pluginParam());
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
    IExternal *iplugin_info = qobject_cast<IExternal *>(obj);
    if (!iplugin_info) continue;
    iplugin_info->init(this);
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
