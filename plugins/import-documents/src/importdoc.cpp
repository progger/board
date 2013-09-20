/*
 * Copyright (C) 2013 Michael Kulabuhov, Kemerovo, Russia.
 *
 * See the LICENSE file for terms of use.
 */

#include <QFileDialog>
#include <QBuffer>
#include <QProcess>
#include <poppler/cpp/poppler-document.h>
#include <poppler/cpp/poppler-page.h>
#include <poppler/cpp/poppler-page-renderer.h>
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
  poppler::document *document = poppler::document::load_from_file(file_name.toStdString());
  int count = document->pages();
  poppler::page_renderer renderer;
  renderer.set_render_hints(poppler::page_renderer::antialiasing |
                            poppler::page_renderer::text_antialiasing |
                            poppler::page_renderer::text_hinting);
  ISheet *sheet = g_core->sheet(g_core->sheetIndex());
  ISheetCanvas *canvas = sheet->canvas();
  int y = canvas->sheetPoint().y();
  QQmlComponent *image_comp = g_core->getComponent("qrc:/core/qml/ImageWrapper.qml");
  Q_ASSERT(image_comp);
  for (int i = 0; i < count; i++)
  {
    poppler::page *page = document->create_page(i);
    poppler::image pdf_image = renderer.render_page(page, 128, 128);
    delete page;
    QQuickItem *image = qobject_cast<QQuickItem*>(image_comp->create());
    Q_ASSERT(image);

    image->setParent(canvas->container());
    image->setParentItem(canvas->container());
    image->setZ(canvas->getZNext());
    image->setPosition(QPointF((canvas->container()->width() - pdf_image.width()) / 2, y));
    image->setSize(QSizeF(pdf_image.width(), pdf_image.height()));

    QImage::Format format;
    switch (pdf_image.format()) {
      case poppler::image::format_mono:
        format = QImage::Format_Mono;
        break;
      case poppler::image::format_rgb24:
        format = QImage::Format_RGB888;
        break;
      case poppler::image::format_argb32:
        format = QImage::Format_ARGB32;
        break;
      default:
        return;
    }
    QImage qt_image((uchar*)pdf_image.data(), pdf_image.width(), pdf_image.height(), format);
    QByteArray data;
    QBuffer buffer(&data);
    buffer.open(QIODevice::WriteOnly);
    qt_image.save(&buffer, "PNG");
    buffer.close();
    QString hash = g_core->brdStore()->addObject(data);
    image->setProperty("hash", hash);

    y += pdf_image.height();
  }
  delete document;
  delete dir;
  canvas->updateSheetRect();
}

QString ImportDoc::convert(const QString &file_name, QTemporaryDir *dir)
{
  QProcess process;
  process.start(QString("soffice --headless --convert-to pdf --outdir \"%1\" \"%2\"").arg(dir->path(), file_name));
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
