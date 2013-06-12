/*
 * Copyright (C) 2012 Kulabuhov Michael, Kemerovo, Russia.
 *
 * See the LICENSE file for terms of use.
 */

#include "global.h"
#include "core.h"
#include "mainview.h"

MainView::MainView(QWindow *parent) :
  QQuickView(parent)
{
  g_core = new Core(this);
  setResizeMode(QQuickView::SizeRootObjectToView);
  setSource(QUrl("qrc:/core/qml/Board.qml"));
}
