/*
 * Copyright (C) 2013 Michael Kulabuhov, Kemerovo, Russia.
 *
 * See the LICENSE file for terms of use.
 */

#include "global.h"
#include "importdoc.h"
#include "plugin.h"

Plugin::Plugin(QObject *parent) :
  QObject(parent)
{
}

void Plugin::init()
{
  qmlRegisterSingletonType<ImportDoc>("board.importdocuments", 2, 0, "ImportDoc",
                                   [](QQmlEngine *, QJSEngine *) -> QObject*
  {
    return new ImportDoc();
  });
  g_core->addPluginRowItem("qrc:/import-documents/qml/ImportDocumentsButton.qml");
}
