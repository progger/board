/*
 * Copyright (C) 2012 Kulabuhov Michael, Kemerovo, Russia.
 *
 * See the LICENSE file for terms of use.
 */

#include <QtPlugin>
#include "crosswordinfo.h"

void CrosswordInfo::init(ICore *core)
{
  core->addPlugin("Кроссворд", "");
  core->addPlugin("Кроссворд/Первый", "", "crossword", QStringList("1"));
  core->addPlugin("Кроссворд/Второй", "", "crossword", QStringList("2"));
  core->addPlugin("Кроссворд/Третий", "", "crossword", QStringList("3"));
}

Q_EXPORT_PLUGIN2(IPluginInfo, CrosswordInfo)
