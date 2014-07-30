/*
 * Copyright (C) 2014 Michael Kulabuhov, Kemerovo, Russia.
 *
 * See the LICENSE file for terms of use.
 */

#include "global.h"
#include "cardtransform.h"
#include "transformbutton.h"
#include "plugin.h"

Plugin::Plugin(QObject *parent) :
  QObject(parent)
{
}

void Plugin::init()
{
  qmlRegisterType<CardTransform>("board.transform", 2, 0, "CardTransform");
  qmlRegisterType<TransformButton>("board.transform", 2, 0, "TransformButton");
  qmlRegisterType<Card>();
  //g_core->addPluginRowItem("qrc:/transform/qml/TransformButton.qml");
  g_core->paint()->RegisterShape("transform", []() -> Shape* { return static_cast<Shape*>(g_core->getComponent("qrc:/transform/qml/CardTransform.qml")->create()); });
}
