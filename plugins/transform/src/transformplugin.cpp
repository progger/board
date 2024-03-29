/*
 * Copyright (C) 2014 Michael Kulabuhov, Kemerovo, Russia.
 *
 * See the LICENSE file for terms of use.
 */

#include "global.h"
#include "cardtransform.h"
#include "transformbutton.h"
#include "transformplugin.h"

TransformPlugin::TransformPlugin(QObject *parent) :
  QObject(parent)
{
}

void TransformPlugin::init()
{
  qmlRegisterType<CardTransform>("board.transform", 2, 0, "CardTransform");
  qmlRegisterType<TransformButton>("board.transform", 2, 0, "TransformButton");
  qmlRegisterAnonymousType<Card>("board.transform", 1);
  QQmlComponent *component = g_core->getComponent("qrc:/transform/qml/TransformButton.qml");
  g_core->registerTool("transform", "common", component, 1, 1);
  g_core->paint()->RegisterShape("transform", []() -> Shape* { return static_cast<Shape*>(g_core->getComponent("qrc:/transform/qml/CardTransform.qml")->create()); });
}
