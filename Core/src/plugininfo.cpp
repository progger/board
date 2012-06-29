/*
 * Copyright (C) 2012 Kulabuhov Michael, Kemerovo, Russia.
 *
 * See the LICENSE file for terms of use.
 */

#include "plugininfo.h"

PluginInfo::PluginInfo(IPluginInfo *plugin_info, QString &lib_name, QObject *parent) :
  QObject(parent),
  plugin_info_(plugin_info),
  lib_name_(lib_name)
{
}

QString PluginInfo::name()
{
  return plugin_info_->name();
}

QString PluginInfo::image()
{
  return plugin_info_->image();
}
