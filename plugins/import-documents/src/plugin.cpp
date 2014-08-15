/*
 * Copyright (C) 2013 Michael Kulabuhov, Kemerovo, Russia.
 *
 * See the LICENSE file for terms of use.
 */

#include "global.h"
#include "importdoc.h"
#include "pdfviewer.h"
#include "plugin.h"

Plugin::Plugin(QObject *parent) :
  QObject(parent)
{
}

void Plugin::init()
{
  qmlRegisterType<PdfViewer>("board.importdocuments", 2, 0, "PdfViewer");
  qmlRegisterSingletonType<ImportDoc>("board.importdocuments", 2, 0, "ImportDoc",
                                   [](QQmlEngine *, QJSEngine *) -> QObject*
  {
    return new ImportDoc();
  });
  g_core->registerTool("import-documents", "Импорт", "qrc:/import-documents/qml/ImportDocumentsButton.qml");
  g_core->paint()->RegisterShape("PdfViewer", []() -> Shape* { return static_cast<Shape*>(g_core->getComponent("qrc:/import-documents/qml/PdfViewer.qml")->create()); });
}
