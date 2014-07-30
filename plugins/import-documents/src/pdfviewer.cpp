/*
 * Copyright (C) 2013 Michael Kulabuhov, Kemerovo, Russia.
 *
 * See the LICENSE file for terms of use.
 */

#include <QImage>
#include <QBuffer>
#include "global.h"
#include "pdfviewer.h"

PdfViewer::PdfViewer(QQuickItem *parent) :
  Shape(parent),
  _hash(),
  _page(0),
  _page_count(0),
  _image_id(0),
  _image_source(),
  _image_width(0),
  _image_height(0),
  _document(nullptr)
{
  connect(this, SIGNAL(imageWidthChanged()), SLOT(onImageSizeChanged()));
  connect(this, SIGNAL(imageHeightChanged()), SLOT(onImageSizeChanged()));
}

PdfViewer::~PdfViewer()
{
  if (_image_id)
  {
    g_core->brdStore()->removeTempObject(_image_id);
  }
}

void PdfViewer::setPdf(const QByteArray &pdf_content)
{
  _hash = g_core->brdStore()->addObject(pdf_content);
  createDocument(pdf_content);
  setPage(0);
}

void PdfViewer::setPage(int page)
{
  _page = page;
  createImage();
  emit pageChanged();
}

void PdfViewer::setImageWidth(qreal width)
{
  _image_width = width;
  emit imageWidthChanged();
}

void PdfViewer::setImageHeight(qreal height)
{
  _image_height = height;
  emit imageHeightChanged();
}

QString PdfViewer::elementName() const
{
  return "PdfViewer";
}

void PdfViewer::innerSerialize(QXmlStreamWriter *writer, QSet<QString> *brd_objects) const
{
  writer->writeAttribute("hash", _hash);
  writer->writeAttribute("page", QString::number(_page));
  if (brd_objects) brd_objects->insert(_hash);
}

void PdfViewer::innerDeserialize(QXmlStreamReader *reader)
{
  _hash = reader->attributes().value("hash").toString();
  QByteArray pdf_content = g_core->brdStore()->getObject(_hash);
  createDocument(pdf_content);
  setPage(reader->attributes().value("page").toString().toInt());
}

void PdfViewer::onImageSizeChanged()
{
  createImage();
}

void PdfViewer::createDocument(const QByteArray &pdf_content)
{
  _document = QSharedPointer<Poppler::Document>(Poppler::Document::loadFromData(pdf_content));
  if (_document)
  {
    _document->setRenderHint(Poppler::Document::Antialiasing);
    _document->setRenderHint(Poppler::Document::TextAntialiasing);
    _document->setRenderHint(Poppler::Document::TextHinting);
    _page_count = _document->numPages();
  }
  else
  {
    _page_count = 0;
  }
  emit pageCountChanged();
}

void PdfViewer::createImage()
{
  if (_image_id)
  {
    g_core->brdStore()->removeTempObject(_image_id);
    _image_source = QString();
  }
  if (_document && _page >= 0 && _page < _document->numPages())
  {
    Poppler::Page *page = _document->page(_page);
    QSizeF size = page->pageSizeF();
    qreal kw = _image_width / size.width();
    qreal kh = _image_height / size.height();
    qreal k = qMin(kw, kh);
    QImage image = page->renderToImage(72 * k, 72 * k);
    QByteArray data;
    QBuffer buffer(&data);
    buffer.open(QIODevice::WriteOnly);
    image.save(&buffer, "PNG");
    buffer.close();
    _image_id = g_core->brdStore()->addTempObject(data);
    _image_source = g_core->brdStore()->getTempUrl(_image_id);
  }
  emit imageSourceChanged();
}
