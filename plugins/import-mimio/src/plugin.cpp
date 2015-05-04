/*
 * Copyright (C) 2014 Michael Kulabuhov, Kemerovo, Russia.
 *
 * See the LICENSE file for terms of use.
 */

#include <quazip/quazipfile.h>
#include <QXmlStreamReader>
#include "global.h"
#include "plugin.h"

bool openBookMimio(const QString &file_name);
bool openBookFiles(QuaZip *zip);

Plugin::Plugin(QObject *parent) :
  QObject(parent)
{
}

void Plugin::init()
{
  g_core->registerImporter("Mimio", "ink", openBookMimio);
}

bool openBookMimio(const QString &file_name)
{
  QuaZip zip(file_name);
  if (!zip.open(QuaZip::mdUnzip))
  {
    g_core->showError(QString("Не удалось открыть %1: error %2").arg(file_name).arg(zip.getZipError()));
    return false;
  }
  return openBookFiles(&zip);
}

bool openBookFiles(QuaZip *zip)
{
  if (!zip->setCurrentFile("objects.xml"))
  {
    g_core->showError(QString("Не удалось открыть файл Mimio: %1").arg(zip->getZipError()));
    return false;
  }
  QuaZipFile zip_file(zip);
  if (!zip_file.open(QIODevice::ReadOnly))
  {
    g_core->showError(QString("Не удалось открыть файл Mimio: %1").arg(zip_file.getZipError()));
    return false;
  }
  QXmlStreamReader reader(&zip_file);
  reader.readNextStartElement();
  if (reader.name() != "MIMIO") goto error;
  reader.readNextStartElement();
  if (reader.name() != "DOCUMENT") goto error;
  while (reader.readNextStartElement())
  {
    if (reader.name() != "PAGE") goto error;
    ISheet *sheet = g_core->addSheet();
  }
  return true;
error:
  g_core->showError("Файл Mimio имеет неверный формат");
  return false;
}
