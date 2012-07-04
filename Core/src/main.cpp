/*
 * Copyright (C) 2012 Kulabuhov Michail, Kemerovo, Russia.
 *
 * See the LICENSE file for terms of use.
 */

#include <QtGui/QApplication>
#include <QTextCodec>
#include "mainview.h"

int main(int argc, char *argv[])
{
  QTextCodec::setCodecForCStrings(QTextCodec::codecForName("utf8"));
  QApplication app(argc, argv);
  app.setGraphicsSystem("opengl");
  MainView view;
  view.showFullScreen();
  return app.exec();
}
