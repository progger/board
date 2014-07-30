/*
 * Copyright (C) 2014 Michael Kulabuhov, Kemerovo, Russia.
 *
 * See the LICENSE file for terms of use.
 */

#ifndef TRANSFORMBUTTON_H
#define TRANSFORMBUTTON_H

#include <QQuickItem>

class TransformButton : public QQuickItem
{
  Q_OBJECT
public:
  explicit TransformButton(QQuickItem *parent = 0);
public slots:
  void placeTransform();
};

#endif // TRANSFORMBUTTON_H
