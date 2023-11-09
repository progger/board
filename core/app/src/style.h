/*
 * Copyright (C) 2013 Michael Kulabuhov, Kemerovo, Russia.
 *
 * See the LICENSE file for terms of use.
 */

#ifndef STYLE_H
#define STYLE_H

#include <QQuickItem>

class Style : public QQuickItem
{
  Q_OBJECT
  Q_DISABLE_COPY_MOVE(Style)
public:
  explicit Style(QQuickItem *parent = nullptr);
  ~Style() override = default;
};

#endif // STYLE_H
