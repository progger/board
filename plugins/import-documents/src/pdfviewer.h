/*
 * Copyright (C) 2013 Michael Kulabuhov, Kemerovo, Russia.
 *
 * See the LICENSE file for terms of use.
 */

#ifndef PDFVIEWER_H
#define PDFVIEWER_H

#include <QSharedPointer>
#include <QtGlobal>
#ifdef Q_OS_WIN
#include <poppler-qt5.h>
#else
#include <poppler/qt5/poppler-qt5.h>
#endif
#include "shape.h"

class PdfViewer : public Shape
{
  Q_OBJECT
  Q_PROPERTY(int page READ page WRITE setPage NOTIFY pageChanged)
  Q_PROPERTY(int pageCount READ pageCount NOTIFY pageCountChanged)
  Q_PROPERTY(QString imageSource READ imageSource NOTIFY imageSourceChanged)
  Q_PROPERTY(qreal imageWidth READ imageWidth WRITE setImageWidth NOTIFY imageWidthChanged)
  Q_PROPERTY(qreal imageHeight READ imageHeight WRITE setImageHeight NOTIFY imageHeightChanged)
public:
  explicit PdfViewer(QQuickItem *parent = 0);
  virtual ~PdfViewer() override;
  void setPdf(const QByteArray &pdf_content);
  int page() const { return _page; }
  int pageCount() const { return _page_count; }
  QString imageSource() const { return _image_source; }
  int imageWidth() const { return _image_width; }
  int imageHeight() const { return _image_height; }
public slots:
  void setPage(int page);
  void setImageWidth(qreal width);
  void setImageHeight(qreal height);
signals:
  void pageChanged();
  void pageCountChanged();
  void imageSourceChanged();
  void imageWidthChanged();
  void imageHeightChanged();
protected:
  virtual QString elementName() const override;
  virtual void innerSerialize(QXmlStreamWriter *writer, QSet<QString> *brd_objects) const override;
  virtual void innerDeserialize(QXmlStreamReader *reader) override;
private slots:
  void onImageSizeChanged();
private:
  QString _hash;
  int _page;
  int _page_count;
  int _image_id;
  QString _image_source;
  qreal _image_width;
  qreal _image_height;
  QSharedPointer<Poppler::Document> _document;
  void createDocument(const QByteArray &pdf_content);
  void createImage();
};

#endif // PDFVIEWER_H
