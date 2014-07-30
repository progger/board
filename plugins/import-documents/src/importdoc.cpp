/*
 * Copyright (C) 2013 Michael Kulabuhov, Kemerovo, Russia.
 *
 * See the LICENSE file for terms of use.
 */

#include <QProcess>
#ifdef Q_OS_WIN
#include <poppler-qt5.h>
#else
#include <poppler/qt5/poppler-qt5.h>
#endif
#include "global.h"
#include "pdfviewer.h"
#include "importdoc.h"

ImportDoc::ImportDoc(QObject *parent) :
  QObject(parent)
{
}

void ImportDoc::importDoc(const QUrl &file_url)
{
  QString file_name = file_url.toLocalFile();
  QSharedPointer<QTemporaryDir> dir = QSharedPointer<QTemporaryDir>();
  if (QFileInfo(file_name).suffix().compare("pdf", Qt::CaseInsensitive) != 0)
  {
    dir = QSharedPointer<QTemporaryDir>::create();
    file_name = convert(file_name, dir);
    if (file_name.isEmpty()) return;
  }
  QFile file(file_name);
  if (!file.open(QIODevice::ReadOnly))
  {
    g_core->showError("Не удалось открыть файл " + file_name);
    return;
  }
  QByteArray pdf_content = file.readAll();
  Poppler::Document *document = Poppler::Document::loadFromData(pdf_content);
  if (!document)
  {
    g_core->showError("Не удалось загрузить документ");
    return;
  }
  delete document;

  ISheet *sheet = g_core->sheet(g_core->sheetIndex());
  ISheetCanvas *canvas = sheet->canvas();
  QQmlComponent *component = g_core->getComponent("qrc:/import-documents/qml/PdfViewer.qml");
  PdfViewer *viewer = qobject_cast<PdfViewer*>(component->create());
  Q_ASSERT(viewer);
  viewer->init(canvas);
  viewer->setZ(canvas->getZNext());
  QSizeF size = QSizeF(canvas->container()->width() / 2, canvas->container()->height() / 1.5);
  viewer->setPosition(QPointF((canvas->container()->width() - size.width()) / 2,
                              (canvas->container()->height() - size.height()) / 2));
  viewer->setSize(size);
  viewer->setPdf(pdf_content);
  canvas->pushState();
  canvas->updateSheetRect();
}

QString ImportDoc::convert(const QString &file_name, QSharedPointer<QTemporaryDir> dir)
{
  QProcess process;
#ifdef Q_OS_WIN
  QString soffice_name = "soffice.exe";
  QSettings settings("HKEY_LOCAL_MACHINE\\SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\App Paths\\soffice.exe", QSettings::NativeFormat);
  if (settings.contains("."))
  {
    soffice_name = settings.value(".", "").toString();
  }
  process.start(QString("\"%1\" --headless --convert-to pdf --outdir \"%2\" \"%3\"").arg(soffice_name, dir->path(), file_name));
#else
  process.start(QString("soffice --headless --convert-to pdf --outdir \"%1\" \"%2\"").arg(dir->path(), file_name));
#endif
  if (!process.waitForFinished())
  {
    g_core->showError("Не удалось импортировать документ");
  }
  QFileInfoList files = QDir(dir->path()).entryInfoList(QDir::Files);
  if (files.count())
  {
    return files.first().filePath();
  }
  return QString();
}
