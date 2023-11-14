/*
 * Copyright (C) 2015 Michael Kulabuhov, Kemerovo, Russia.
 *
 * See the LICENSE file for terms of use.
 */

#include "global.h"
#include "importer.h"
#include "importmimioplugin.h"

bool openBookMimio(const QString &file_name);

ImportMimioPlugin::ImportMimioPlugin(QObject *parent) :
  QObject(parent)
{
}

void ImportMimioPlugin::init()
{
  g_core->registerImporter("Mimio", "ink", openBookMimio);
}

bool openBookMimio(const QString &file_name)
{
  Importer importer;
  return importer.import(file_name);
}
