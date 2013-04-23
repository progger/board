/*
 * Copyright (C) 2012 Kulabuhov Michael, Kemerovo, Russia.
 *
 * See the LICENSE file for terms of use.
 */

#include <QtOpenGL/QGLFormat>
#include <QtOpenGL/QGLWidget>
#include "global.h"
#include "mainview.h"
#include "core.h"

MainView::MainView(QWindow *parent) :
  QQuickView(parent)
{
  //connect(this, SIGNAL(windowStateChanged(Qt::WindowState)), SLOT(onWindowStateChanged(Qt::WindowState)));
  auto core = new Core(this);
  setResizeMode(QQuickView::SizeRootObjectToView);
  setSource(QUrl("qrc:/core/qml/Board.qml"));
  core->init();
}
/*
void MainView::onWindowStateChanged(Qt::WindowState windowState)
{
  windowState = Qt::WindowNoState;
  if (windowState == Qt::WindowNoState)
  {
    //showFullScreen();
  }
}
*/
