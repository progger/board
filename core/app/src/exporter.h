/*
 * Copyright (C) 2015 Michael Kulabuhov, Kemerovo, Russia.
 *
 * See the LICENSE file for terms of use.
 */

#ifndef EXPORTER_H
#define EXPORTER_H

#include <QObject>
#include "icore.h"

class Exporter : public QObject
{
  Q_OBJECT
  Q_PROPERTY(QString name READ name CONSTANT)
  Q_PROPERTY(QString suffix READ suffix CONSTANT)
public:
  explicit Exporter(const QString &name, const QString &suffix, ExportFunc func, QObject *parent = 0);
  QString name() const { return _name; }
  QString suffix() const { return _suffix; }
  ExportFunc func() const { return _func; }
private:
  QString _name;
  QString _suffix;
  ExportFunc _func;
};

#endif // EXPORTER_H
