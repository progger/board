/*
 * Copyright (C) 2015 Michael Kulabuhov, Kemerovo, Russia.
 *
 * See the LICENSE file for terms of use.
 */

#include "importer.h"

Importer::Importer(const QString &name, const QString &suffix, ImportFunc func, QObject *parent) :
  QObject(parent),
  _name(name),
  _suffix(suffix),
  _func(func)
{
}
