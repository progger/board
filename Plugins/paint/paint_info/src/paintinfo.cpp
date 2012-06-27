/*
 * Copyright (C) 2012 Kulabuhov Michael, Kemerovo, Russia.
 *
 * See the LICENSE file for terms of use.
 */

#include <QtPlugin>
#include "paintinfo.h"

QString PaintInfo::name()
{
  return "Paint";
}

QString PaintInfo::image()
{
  return "qrc:/plugin_info/paint/res/logo.svg";
}

Q_EXPORT_PLUGIN2(IPluginInfo, PaintInfo)
