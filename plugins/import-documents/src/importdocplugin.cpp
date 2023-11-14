/*
 * Copyright (C) 2013 Michael Kulabuhov, Kemerovo, Russia.
 *
 * See the LICENSE file for terms of use.
 */

#include "global.h"
#include "importdoc.h"
#include "pdfviewer.h"
#include "importdocplugin.h"

ImportDocPlugin::ImportDocPlugin(QObject *parent) :
  QObject(parent)
{
}

void ImportDocPlugin::init()
{
  qmlRegisterType<PdfViewer>("board.importdocuments", 2, 0, "PdfViewer");
  qmlRegisterSingletonType<ImportDoc>("board.importdocuments", 2, 0, "ImportDoc",
                                   [](QQmlEngine *, QJSEngine *) -> QObject*
  {
    return new ImportDoc();
  });
  QQmlComponent *component = g_core->getComponent("qrc:/import-documents/qml/ImportDocumentsButton.qml");
  g_core->registerTool("import-documents", "Импорт", component, 1, 1);
  g_core->paint()->RegisterShape("PdfViewer", []() -> Shape* { return static_cast<Shape*>(g_core->getComponent("qrc:/import-documents/qml/PdfViewer.qml")->create()); });
}
