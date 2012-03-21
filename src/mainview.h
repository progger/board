/*
 * Copyright (C) 2011 Kulabuhov Michael, Kemerovo, Russia.
 *
 * See the LICENSE file for terms of use.
 */

#ifndef MAINVIEW_H
#define MAINVIEW_H

#include <QDeclarativeView>

class MainView : public QDeclarativeView
{
  Q_OBJECT
public:
  explicit MainView(QWidget *parent = 0);
};

#endif // MAINVIEW_H
