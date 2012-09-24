/*
 * Copyright (C) 2012 Kulabuhov Michael, Kemerovo, Russia.
 *
 * See the LICENSE file for terms of use.
 */

#ifndef PATHPROCESSOR_H
#define PATHPROCESSOR_H

#include <QObject>
#include <QVariant>

class PathProcessor : public QObject
{
  Q_OBJECT
  Q_PROPERTY(QVariantList arx READ arx)
  Q_PROPERTY(QVariantList ary READ ary)

public:
  explicit PathProcessor(QObject *parent = 0);
  QVariantList &arx() { return arx_; }
  QVariantList &ary() { return ary_; }
  Q_INVOKABLE bool process(QVariantList arx, QVariantList ary);

public slots:
  void clear();

private:
  QVariantList arx_;
  QVariantList ary_;
};

#endif // PATHPROCESSOR_H
