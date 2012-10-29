/*
 * Copyright (C) 2012 Kulabuhov Michael, Kemerovo, Russia.
 *
 * See the LICENSE file for terms of use.
 */

#ifndef CROSSEDIT_H
#define CROSSEDIT_H

#include "icross.h"

class Crossedit : public QObject
{
  Q_OBJECT
  Q_PROPERTY(int width READ width NOTIFY updateWidth FINAL)
  Q_PROPERTY(int height READ height NOTIFY updateHeight FINAL)
  Q_PROPERTY(QObject *grid READ grid CONSTANT FINAL)
  Q_PROPERTY(QObjectList words READ words CONSTANT FINAL)
public:
  explicit Crossedit(QObject *parent, ICross *cross);
  int width() { return width_; }
  int height() { return height_; }
  QObject *grid() { return grid_->toQObject(); }
  QObjectList words() { return words_; }
signals:
  void updateWidth();
  void updateHeight();
public slots:
private:
  ICross *cross_;
  int width_;
  int height_;
  IGrid *grid_;
  QObjectList words_;
};

#endif // CROSSEDIT_H
