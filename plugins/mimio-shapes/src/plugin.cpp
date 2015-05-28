/*
 * Copyright (C) 2015 Michael Kulabuhov, Kemerovo, Russia.
 *
 * See the LICENSE file for terms of use.
 */

#include "global.h"
#include "mimiotext.h"
#include "plugin.h"

Plugin::Plugin(QObject *parent) :
  QObject(parent)
{
}

void Plugin::init()
{
  qmlRegisterType<MimioText>("board.mimio", 2, 0, "MimioText");
  g_core->paint()->RegisterShape("mimio-text", []() -> Shape* { return static_cast<Shape*>(g_core->getComponent("qrc:/mimio-shapes/qml/MimioText.qml")->create()); });
}
