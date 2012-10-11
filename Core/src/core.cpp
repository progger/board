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
  plugin_mode_(false),
  menu_visible_(false),
  keyboard_(false),
  load_plugin_(false),
  libs_(),
  root_plugin_info_(new PluginInfo(this, QString())),
  plugin_info_(nullptr),
  loader_(nullptr)
{
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
  if (load_plugin_)
    emit addPluginWebObject(name, obj);
  else
    emit addLibWebObject(name, obj);
}

void Core::loadWebPage(const QString &url)
{
  emit loadWebViewPage(url);
}

void Core::loadLib(const QString &lib_name)
{
  if (libs_.contains(lib_name)) return;
  auto dir = QDir(QApplication::applicationDirPath());
  if (!dir.cd("libs")) return;
  auto file_name = lib_name + ".lib";
  if (!dir.exists(file_name)) return;
  file_name = dir.filePath(file_name);
  auto loader = new QPluginLoader(file_name, this);
  QObject *lib_obj = loader->instance();
  if (!lib_obj) return;
  IExternal *lib = qobject_cast<IExternal*>(lib_obj);
  if (!lib) return;
  load_plugin_ = false;
  lib->init(this);
  libs_.push_back(lib_name);
}

void Core::loadLibs(const QStringList &libs)
{
  foreach (auto lib_name, libs)
  {
    loadLib(lib_name);
  }
}

QObject *Core::mainView()
{
  return parent();
}

void Core::init()
{
  auto args = QCoreApplication::arguments();
  if (args.length() > 1 && loadPluginInternal(args.at(1), args.mid(2)))
  {
    plugin_mode_ = true;
  }
  else
  {
    loadPluginInfo();
    setMenuVisible(true);
  }
}

void Core::emulateKeyPress(int key, int modifiers, const QString &text) const
{
  KeyboardModifiers md = KeyboardModifiers(modifiers);
  QKeyEvent *event = new QKeyEvent(QEvent::KeyPress, key, md, text);
  QApplication::postEvent(QApplication::focusWidget(), event);
}

void Core::selectPlugin(QObject *obj)
{
  auto *plugin_info = qobject_cast<PluginInfo*>(obj);
  if (!plugin_info) return;
  if (loadPluginInternal(plugin_info->pluginName(), plugin_info->pluginParam()))
  {
    plugin_info_ = plugin_info;
    setMenuVisible(false);
  }
}

void Core::loadPluginInfo()
{
  auto dir = QDir(QApplication::applicationDirPath());
  if (!dir.cd("plugins")) return;
  QStringList filter("*.info");
  auto files = dir.entryInfoList(filter, QDir::Files);
  foreach (auto file_info, files)
  {
    auto *loader = new QPluginLoader(file_info.filePath(), this);
    QObject* obj = loader->instance();
    if (!obj) continue;
    IExternal *iplugin_info = qobject_cast<IExternal *>(obj);
    if (!iplugin_info) continue;
    iplugin_info->init(this);
  }
  emit updatePluginInfo();
}

bool Core::loadPluginInternal(const QString &plugin_name, const QStringList &param)
{
  emit unloadPlugin();
  delete loader_;
  QDir dir = QDir(QApplication::applicationDirPath());
  if (!dir.cd("plugins")) return false;
  QString file_name = plugin_name + ".plugin";
  if (!dir.exists(file_name)) return false;
  file_name = dir.filePath(file_name);
  loader_ = new QPluginLoader(file_name, this);
  QObject *plugin_obj = loader_->instance();
  if (!plugin_obj) return false;
  IPlugin *plugin = qobject_cast<IPlugin*>(plugin_obj);
  if (!plugin) return false;
  load_plugin_ = true;
  plugin->init(this, param);
  emit loadPlugin();
  return true;
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
