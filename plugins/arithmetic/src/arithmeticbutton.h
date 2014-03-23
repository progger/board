/*
 * Copyright (C) 2014 Michael Kulabuhov, Kemerovo, Russia.
 *
 * See the LICENSE file for terms of use.
 */

#ifndef ARITHMETICBUTTON_H
#define ARITHMETICBUTTON_H

#include <QQuickItem>

class ArithmeticButton : public QQuickItem
{
  Q_OBJECT
public:
  explicit ArithmeticButton(QQuickItem *parent = 0);
public slots:
  void placeArithmetic();
};

#endif // ARITHMETICBUTTON_H
