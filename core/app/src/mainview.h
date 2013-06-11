/*
 * Copyright (C) 2012 Kulabuhov Michael, Kemerovo, Russia.
 *
 * See the LICENSE file for terms of use.
 */

#ifndef MAINVIEW_H
#define MAINVIEW_H

#include <QQuickView>

class MainView : public QQuickView
{
  Q_OBJECT
public:
  explicit MainView(QWindow *parent = 0);
//private slots:
//  void onWindowStateChanged(Qt::WindowState windowState);
};

#endif // MAINVIEW_H
