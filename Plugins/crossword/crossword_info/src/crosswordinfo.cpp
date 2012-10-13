/*
 * Copyright (C) 2012 Kulabuhov Michael, Kemerovo, Russia.
 *
 * See the LICENSE file for terms of use.
 */

#include <QtPlugin>
#include "crosswordinfo.h"

void CrosswordInfo::init(ICore *core)
{
  core->addPlugin("Кроссворд", ":/plugin_info/crossword/res/logo.svg");
  core->addPlugin("Кроссворд/Зима", ":/plugin_info/crossword/res/logo.svg", "crossword", QStringList(":/plugin/res/winter.txt"));
}

Q_EXPORT_PLUGIN2(IPluginInfo, CrosswordInfo)
