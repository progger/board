/*
 * Copyright (C) 2014 Michael Kulabuhov, Kemerovo, Russia.
 *
 * See the LICENSE file for terms of use.
 */

#include "global.h"
#include "blackyellow.h"
#include "blackyellowbutton.h"
#include "plugin.h"

Plugin::Plugin(QObject *parent) :
  QObject(parent)
{
}

void Plugin::init()
{
  qmlRegisterType<BlackYellow>("board.blackyellow", 2, 0, "BlackYellow");
  qmlRegisterType<BlackYellowButton>("board.blackyellow", 2, 0, "BlackYellowButton");
  qmlRegisterAnonymousType<BlackYellowItem>("board.blackyellow", 1);
  QQmlComponent *component = g_core->getComponent("qrc:/black-yellow/qml/BlackYellowButton.qml");
  g_core->registerTool("black-yellow", "common", component, 1, 1);
  g_core->paint()->RegisterShape("black-yellow", []() -> Shape* { return static_cast<Shape*>(g_core->getComponent("qrc:/black-yellow/qml/BlackYellow.qml")->create()); });
}
