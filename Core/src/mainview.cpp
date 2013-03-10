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
  //connect(engine(), SIGNAL(quit()), SLOT(close()));
  auto core = new Core(this);
  setResizeMode(QQuickView::SizeRootObjectToView);
  setSource(QUrl("qrc:/core/qml/Board.qml"));
  core->init();
  /*
  if (global_mode_opengl)
  {
    QGLFormat format = QGLFormat(QGL::SingleBuffer | QGL::Rgba | QGL::DirectRendering | QGL::SampleBuffers);
    QGLWidget *widget = new QGLWidget(format);
    widget->setAutoFillBackground(false);
    setViewport(widget);
  }
  */
}
