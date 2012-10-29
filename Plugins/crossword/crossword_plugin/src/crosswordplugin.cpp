/*
 * Copyright (C) 2012 Kulabuhov Michael, Kemerovo, Russia.
 *
 * See the LICENSE file for terms of use.
 */

#include <QtPlugin>
#include "icross.h"
#include "crossword.h"
#include "crosswordplugin.h"

void CrosswordPlugin::init(ICore *core, const QStringList &param)
{
  ICross *cross = qobject_cast<ICross*>(core->loadLib("cross"));
  if (!cross) return;
  auto crossword = new Crossword(this, cross);
  if (!crossword->init(param[0]))
  {
    delete crossword;
    return;
  }
  core->addObject("Crossword", crossword);
  core->addQml(":/plugin/crossword/qml/Field.qml");
}

Q_EXPORT_PLUGIN2(IPlugin, CrosswordPlugin)
