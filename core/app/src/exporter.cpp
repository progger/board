/*
 * Copyright (C) 2015 Michael Kulabuhov, Kemerovo, Russia.
 *
 * See the LICENSE file for terms of use.
 */

#include "exporter.h"

Exporter::Exporter(const QString &name, const QString &suffix, ExportFunc func, QObject *parent) :
  QObject(parent),
  _name(name),
  _suffix(suffix),
  _func(func)
{
}
