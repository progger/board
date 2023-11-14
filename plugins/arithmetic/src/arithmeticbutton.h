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
  Q_DISABLE_COPY_MOVE(ArithmeticButton)
public:
  explicit ArithmeticButton(QQuickItem *parent = nullptr);
  ~ArithmeticButton() override = default;
public slots:
  void placeArithmetic();
};

#endif // ARITHMETICBUTTON_H
