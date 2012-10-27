/*
 * Copyright (C) 2012 Kulabuhov Michael, Kemerovo, Russia.
 *
 * See the LICENSE file for terms of use.
 */

#include <QtPlugin>
#include "crosseditplugin.h"

void CrosseditPlugin::init(ICore *core, const QStringList &param)
{
}

Q_EXPORT_PLUGIN2(IPlugin, CrosseditPlugin)
