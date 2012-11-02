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
#include <QMessageBox>
#include "iexternal.h"
#include "iplugin.h"
#include "menuitem.h"
#include "global.h"
#include "macro.h"
#include "core.h"

#include <QDebug>
#include <QGraphicsObject>

using namespace Qt;

Core::Core(QDeclarativeView *parent) :
  QObject(parent),
  plugin_mode_(false),
  menu_visible_(false),
  keyboard_(false),
  plugin_info_list_(),
  libs_(),
  menu_path_(),
  menu_item_list_(),
  loader_(nullptr)
{
  root_dir_ = QDir::home();
  root_dir_.mkdir("board");
  root_dir_.cd("board");
  settings_ = new QSettings(root_dir_.filePath("settings.ini"), QSettings::IniFormat, this);

  QDeclarativeContext *context = parent->rootContext();
  context->setContextProperty("Core", this);
}

void Core::addPlugin(const QString &name, const QString &image,
                     const QString &plugin_name, const QStringList &plugin_param)
{
  auto menu_item = new MenuItem(this, name, image, plugin_name, plugin_param);
  menu_item_list_.append(menu_item);
}

void Core::addObject(const QString &name, QObject *obj)
{
  QDeclarativeView *view = qobject_cast<QDeclarativeView*>(mainView());
  if (!view) return;
  view->rootContext()->setContextProperty(name, obj);
}

void Core::addQml(const QString &path)
{
  emit addPluginQml(path);
}

QObject * Core::loadLib(const QString &lib_name)
{
  for (QObject *obj : libs_)
  {
    if (obj->objectName() == lib_name) return obj;
  }
  {
    auto dir = QDir(QApplication::applicationDirPath());
    if (!dir.cd("libs")) goto error;
    auto file_name = GET_LIB_NAME(lib_name);
    if (!dir.exists(file_name)) goto error;
    file_name = dir.filePath(file_name);
    auto loader = new QPluginLoader(file_name, this);
    QObject *lib_obj = loader->instance();
    if (!lib_obj) goto error;
    lib_obj->setObjectName(lib_name);
    IExternal *lib = qobject_cast<IExternal*>(lib_obj);
    if (!lib) goto error;
    lib->init(this);
    libs_.append(lib_obj);
    return lib_obj;
  }
error:
  return nullptr;
}

void Core::loadLibs(const QStringList &libs)
{
  foreach (auto lib_name, libs)
  {
    loadLib(lib_name);
  }
}

QObject *Core::getLib(const QString &name)
{
  for (QObject *obj : libs_)
  {
    if (obj->objectName() == name) return obj;
  }
  return nullptr;
}

void Core::showError(const QString &error)
{
  QMessageBox::critical(qobject_cast<QWidget*>(mainView()), "Error", error);
}

void Core::init()
{
  if (!global_plugin.isEmpty() && loadPluginInternal(global_plugin, global_plugin_params))
  {
    plugin_mode_ = true;
  }
  else
  {
    loadPluginInfo();
    updateMenu();
    setMenuVisible(true);
  }
}

void Core::emulateKeyPress(int key, int modifiers, const QString &text) const
{
  KeyboardModifiers md = KeyboardModifiers(modifiers);
  QKeyEvent *event = new QKeyEvent(QEvent::KeyPress, key, md, text);
  QApplication::postEvent(QApplication::focusWidget(), event);
}

void Core::selectMenuItem(QObject *obj)
{
  MenuItem *menu_item = qobject_cast<MenuItem*>(obj);
  if (!menu_item) return;
  if (menu_item->isDir())
  {
    menu_path_ += menu_path_.isEmpty() ? menu_item->name() : "|" + menu_item->name();
    updateMenu();
  }
  else if (loadPluginInternal(menu_item->pluginName(), menu_item->pluginParam()))
  {
    setMenuVisible(false);
  }
}

void Core::upMenu()
{
  int i = menu_path_.lastIndexOf("|");
  if (i >= 0)
  {
    menu_path_.truncate(i);
  }
  else
  {
    menu_path_.clear();
  }
  updateMenu();
}

void Core::quitButton()
{
  if (plugin_mode_ || menu_visible_)
  {
    QApplication::quit();
  }
  else
  {
    setMenuVisible(true);
    setKeyboard(false);
    emit unloadPlugin();
  }
}

void Core::loadPluginInfo()
{
  auto dir = QDir(QApplication::applicationDirPath());
  if (!dir.cd("info")) return;
  auto files = dir.entryInfoList(QDir::Files);
  for (QFileInfo file : files)
  {
    auto loader = new QPluginLoader(file.filePath(), this);
    auto obj = loader->instance();
    if (!obj) continue;
    IPluginInfo *plugin_info = qobject_cast<IPluginInfo *>(obj);
    if (!plugin_info) continue;
    plugin_info_list_.append(plugin_info);
  }
}

void Core::updateMenu()
{
  menu_item_list_.clear();
  for (IPluginInfo *plugin_info : plugin_info_list_)
  {
    plugin_info->init(this, menu_path_);
  }
  emit updateMenuItemList();
}

bool Core::loadPluginInternal(const QString &plugin_name, const QStringList &param)
{
  if (loader_)
  {
    loader_->unload();
    delete loader_;
    loader_ = nullptr;
  }
  QDir dir = QDir(QApplication::applicationDirPath());
  if (!dir.cd("plugins")) return false;
  QString file_name = GET_LIB_NAME(plugin_name);
  if (!dir.exists(file_name)) return false;
  file_name = dir.filePath(file_name);
  loader_ = new QPluginLoader(file_name, this);
  QObject *plugin_obj = loader_->instance();
  if (!plugin_obj) return false;
  IPlugin *plugin = qobject_cast<IPlugin*>(plugin_obj);
  if (!plugin) return false;
  emit loadPlugin();
  plugin->init(this, param);
  return true;
}

void Core::setKeyboard(bool keyboard)
{
  keyboard_ = keyboard;
  emit updateKeyboard();
}

void Core::setMenuVisible(bool menu_visible)
{
  if (menu_visible_ == menu_visible) return;
  menu_visible_ = menu_visible;
  emit updateMenuVisible();
}
