/*
 * Copyright (C) 2012 Kulabuhov Michael, Kemerovo, Russia.
 *
 * See the LICENSE file for terms of use.
 */

#include <QtPlugin>
#include "icross.h"
#include "crossedit.h"
#include "crosseditplugin.h"

void CrosseditPlugin::init(ICore *core, const QStringList &param)
{
  ICross *cross = qobject_cast<ICross*>(core->loadLib("cross"));
  if (!cross) return;
  auto crossedit = new Crossedit(this, cross);
  core->addObject("Crossedit", crossedit);
  core->addQml(":/plugin/crossedit/qml/Field.qml");
}

Q_EXPORT_PLUGIN2(IPlugin, CrosseditPlugin)
