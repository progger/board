/*
 * Copyright (C) 2015 Michael Kulabuhov, Kemerovo, Russia.
 *
 * See the LICENSE file for terms of use.
 */

#ifndef IMPORTER_H
#define IMPORTER_H

#include <QObject>
#include "icore.h"

class Importer : public QObject
{
  Q_OBJECT
  Q_PROPERTY(QString name READ name CONSTANT)
  Q_PROPERTY(QString suffix READ suffix CONSTANT)
public:
  explicit Importer(const QString &name, const QString &suffix, ImportFunc func,  QObject *parent = 0);
  QString name() const { return _name; }
  QString suffix() const { return _suffix; }
  ImportFunc func() const { return _func; }
private:
  QString _name;
  QString _suffix;
  ImportFunc _func;
};

#endif // IMPORTER_H
