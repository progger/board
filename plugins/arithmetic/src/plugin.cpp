/*
 * Copyright (C) 2014 Michael Kulabuhov, Kemerovo, Russia.
 *
 * See the LICENSE file for terms of use.
 */

#include "global.h"
#include "arithmetic.h"
#include "arithmeticbutton.h"
#include "plugin.h"

Plugin::Plugin(QObject *parent) :
  QObject(parent)
{
}

void Plugin::init()
{
  qmlRegisterType<Arithmetic>("board.arithmetic", 2, 0, "Arithmetic");
  qmlRegisterType<ArithmeticButton>("board.arithmetic", 2, 0, "ArithmeticButton");
  qmlRegisterType<ArithmeticItem>();
  //g_core->addPluginRowItem("qrc:/arithmetic/qml/ArithmeticButton.qml");
  g_core->paint()->RegisterShape("arithmetic", []() -> Shape* { return static_cast<Shape*>(g_core->getComponent("qrc:/arithmetic/qml/Arithmetic.qml")->create()); });
}
