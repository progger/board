/*
 * Copyright (C) 2012 Kulabuhov Michael, Kemerovo, Russia.
 *
 * See the LICENSE file for terms of use.
 */

#include <QDeclarativeEngine>
#include <QDeclarativeContext>
#include <QtOpenGL/QGLFormat>
#include <QtOpenGL/QGLWidget>
#include "mainview.h"
#include "core.h"

MainView::MainView(QWidget *parent) :
  QDeclarativeView(parent)
{
  connect(engine(), SIGNAL(quit()), SLOT(close()));
  Core *core = new Core(this);
  setResizeMode(QDeclarativeView::SizeRootObjectToView);
  setSource(QUrl("qrc:/core/qml/Board.qml"));
  QGLFormat format = QGLFormat(QGL::SingleBuffer | QGL::Rgba | QGL::DirectRendering | QGL::SampleBuffers);
  QGLWidget *widget = new QGLWidget(format);
  widget->setAutoFillBackground(false);
  setViewport(widget);
}
