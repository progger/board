/*
 * Copyright (C) 2012 Kulabuhov Michael, Kemerovo, Russia.
 *
 * See the LICENSE file for terms of use.
 */

#include <QtPlugin>
#include "crosswordinfo.h"

void CrosswordInfo::init(ICore *core, QString menu_path)
{
  if (menu_path.isEmpty())
  {
    core->addPlugin("Кроссворд", ":/plugin_info/crossword/res/logo.svg");
  }
  else if (menu_path == "Кроссворд")
  {
    core->addPlugin("Зима", ":/plugin_info/crossword/res/logo.svg", "crossword", QStringList(":/plugin/res/winter.txt"));
  }
}

Q_EXPORT_PLUGIN2(IPluginInfo, CrosswordInfo)
