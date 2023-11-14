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
  Q_DISABLE_COPY_MOVE(TransformButton)
public:
  explicit TransformButton(QQuickItem *parent = nullptr);
  ~TransformButton() override = default;
public slots:
  void placeTransform();
};

#endif // TRANSFORMBUTTON_H
