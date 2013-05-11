/*
 * Copyright (C) 2012 Kulabuhov Michael, Kemerovo, Russia.
 *
 * See the LICENSE file for terms of use.
 */

#include "mainview.h"
#include "core.h"

MainView::MainView(QWindow *parent) :
  QQuickView(parent)
{
  new Core(this);
  setResizeMode(QQuickView::SizeRootObjectToView);
  setSource(QUrl("qrc:/core/qml/Board.qml"));
}
