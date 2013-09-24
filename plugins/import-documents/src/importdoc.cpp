/*
 * Copyright (C) 2013 Michael Kulabuhov, Kemerovo, Russia.
 *
 * See the LICENSE file for terms of use.
 */

#include <QFileDialog>
#include <QBuffer>
#include <QProcess>
#ifdef Q_OS_WIN
#include <poppler-qt5.h>
#else
#include <poppler/qt5/poppler-qt5.h>
#endif
#include "global.h"
#include "importdoc.h"

ImportDoc::ImportDoc(QObject *parent) :
  QObject(parent)
{
}

void ImportDoc::importDoc()
{
  QFileDialog dialog;
  dialog.setAcceptMode(QFileDialog::AcceptOpen);
  if (!dialog.exec()) return;
  QString file_name = dialog.selectedFiles().first();
  QTemporaryDir *dir = nullptr;
  if (QFileInfo(file_name).suffix().compare("pdf", Qt::CaseInsensitive) != 0)
  {
    dir = new QTemporaryDir();
    file_name = convert(file_name, dir);
    if (file_name.isEmpty()) return;
  }
  Poppler::Document *document = Poppler::Document::load(file_name);
  document->setRenderHint(Poppler::Document::Antialiasing);
  document->setRenderHint(Poppler::Document::TextAntialiasing);
  document->setRenderHint(Poppler::Document::TextHinting);
  int count = document->numPages();
  ISheet *sheet = g_core->sheet(g_core->sheetIndex());
  ISheetCanvas *canvas = sheet->canvas();
  int y = canvas->sheetPoint().y();
  QQmlComponent *image_comp = g_core->getComponent("qrc:/core/qml/ImageWrapper.qml");
  Q_ASSERT(image_comp);
  for (int i = 0; i < count; i++)
  {
    Poppler::Page *page = document->page(i);
    QImage pdf_image = page->renderToImage(128, 128);
    delete page;
    QQuickItem *image = qobject_cast<QQuickItem*>(image_comp->create());
    Q_ASSERT(image);

    image->setParent(canvas->container());
    image->setParentItem(canvas->container());
    image->setZ(canvas->getZNext());
    image->setPosition(QPointF((canvas->container()->width() - pdf_image.width()) / 2, y));
    image->setSize(QSizeF(pdf_image.width(), pdf_image.height()));

    QByteArray data;
    QBuffer buffer(&data);
    buffer.open(QIODevice::WriteOnly);
    pdf_image.save(&buffer, "PNG");
    buffer.close();
    QString hash = g_core->brdStore()->addObject(data);
    image->setProperty("hash", hash);

    y += pdf_image.height();
  }
  delete document;
  delete dir;
  canvas->pushState();
  canvas->updateSheetRect();
}

QString ImportDoc::convert(const QString &file_name, QTemporaryDir *dir)
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
