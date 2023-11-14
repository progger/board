/*
 * Copyright (C) 2015 Michael Kulabuhov, Kemerovo, Russia.
 *
 * See the LICENSE file for terms of use.
 */

#include "global.h"
#include "mimiotext.h"
#include "swfplayer.h"
#include "mimioshapesplugin.h"

class QQuickWebViewExperimental : public QObject
{
public:
  static void setFlickableViewportEnabled(bool enable);
};

MimioShapesPlugin::MimioShapesPlugin(QObject *parent) :
  QObject(parent)
{
}

void MimioShapesPlugin::init()
{
  QQuickWebViewExperimental::setFlickableViewportEnabled(false);
  qmlRegisterType<MimioText>("board.mimio", 2, 0, "MimioText");
  qmlRegisterType<SwfPlayer>("board.mimio", 2, 0, "SwfPlayer");
  g_core->paint()->RegisterShape("mimio-text", []() -> Shape* { return static_cast<Shape*>(g_core->getComponent("qrc:/mimio-shapes/qml/MimioText.qml")->create()); });
  g_core->paint()->RegisterShape("swf-player", []() -> Shape* { return static_cast<Shape*>(g_core->getComponent("qrc:/mimio-shapes/qml/SwfPlayer.qml")->create()); });
}
