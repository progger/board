/*
 * Copyright (C) 2012 Michael Kulabuhov, Kemerovo, Russia.
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
protected:
  bool virtual event(QEvent *ev) override;
};

#endif // MAINVIEW_H
