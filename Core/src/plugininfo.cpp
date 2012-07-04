/*
 * Copyright (C) 2012 Kulabuhov Michael, Kemerovo, Russia.
 *
 * See the LICENSE file for terms of use.
 */

#include "plugininfo.h"

PluginInfo::PluginInfo(QObject *parent, const QString &name) :
  QObject(parent),
  image_(),
  plugin_name_(),
  plugin_param_()
{
  setObjectName(name);
}

bool PluginInfo::isDir()
{
  return plugin_name_.isEmpty();
}

void PluginInfo::setImage(const QString &image)
{
  image_ = image;
  emit updateImage();
}

void PluginInfo::setPluginName(const QString &plugin_name)
{
  plugin_name_ = plugin_name;
}

void PluginInfo::setPluginParam(const QStringList &plugin_param)
{
  plugin_param_ = plugin_param;
}
