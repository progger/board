/*
 * Copyright (C) 2014 Michael Kulabuhov, Kemerovo, Russia.
 *
 * See the LICENSE file for terms of use.
 */

#ifndef BLACKYELLOWBUTTON_H
#define BLACKYELLOWBUTTON_H

#include <QQuickItem>

class BlackYellowButton : public QQuickItem
{
  Q_OBJECT
  Q_DISABLE_COPY_MOVE(BlackYellowButton)
public:
  explicit BlackYellowButton(QQuickItem *parent = nullptr);
  ~BlackYellowButton() override = default;
public slots:
  void placeBlackYellow();
};

#endif // BLACKYELLOWBUTTON_H
