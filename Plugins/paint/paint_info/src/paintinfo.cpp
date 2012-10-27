/*
 * Copyright (C) 2012 Kulabuhov Michael, Kemerovo, Russia.
 *
 * See the LICENSE file for terms of use.
 */

#include <QtPlugin>
#include "paintinfo.h"

void PaintInfo::init(ICore *core, QString menu_path)
{
  if (menu_path.isEmpty())
  {
    core->addPlugin("Paint", "qrc:/plugin_info/paint/res/logo.svg", "paint");
  }
}

Q_EXPORT_PLUGIN2(IPluginInfo, PaintInfo)
