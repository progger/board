/*
 * Copyright (C) 2012 Kulabuhov Michail, Kemerovo, Russia.
 *
 * See the LICENSE file for terms of use.
 */

#include <QtGui/QApplication>
#include "mainview.h"

int main(int argc, char *argv[])
{
  QApplication app(argc, argv);
  app.setGraphicsSystem("opengl");
  MainView view;
  view.showFullScreen();
  return app.exec();
}
