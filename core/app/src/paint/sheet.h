/*
 * Copyright (C) 2013 Michael Kulabuhov, Kemerovo, Russia.
 *
 * See the LICENSE file for terms of use.
 */

#ifndef SHEET_H
#define SHEET_H

#include <QQuickItem>
#include "sheetcanvas.h"
#include "isheet.h"

class Sheet : public QQuickItem, public ISheet
{
  Q_OBJECT
  Q_INTERFACES(ISheet)
  Q_DISABLE_COPY_MOVE(Sheet)
  Q_PROPERTY(bool scrollable READ scrollable WRITE setScrollable NOTIFY scrollableChanged)
  Q_PROPERTY(QColor color READ color WRITE setColor NOTIFY colorChanged)
  Q_PROPERTY(QString imageSource READ imageSource NOTIFY imageSourceChanged)
  Q_PROPERTY(int imageMode READ imageMode WRITE setImageMode NOTIFY imageModeChanged)
public:
  explicit Sheet(QQuickItem *parent = nullptr);
  ~Sheet() override = default;

  // ISheet
public:
  ISheetCanvas *canvas() override;
  bool scrollable() override;
  QColor color() override;
  QString imageHash() override;
  QString imageSource() override;
  int imageMode() override;
public slots:
  void setScrollable(bool scrollable) override;
  void setColor(QColor color) override;
  void setImageHash(const QString &image_hash) override;
  void setImageMode(int image_mode) override;
signals:
  void scrollableChanged() override;
  void colorChanged() override;
  void imageSourceChanged() override;
  void imageModeChanged() override;

public:
  void serialize(QXmlStreamWriter *writer, QSet<QString> *brd_objects = nullptr);
  void deserialize(QXmlStreamReader *reader);
public slots:
  void copySettings(Sheet *sheet);
  void selectImage(const QUrl &file_url);
  void deleteImage();
protected:
  void componentComplete() override;
private:
  SheetCanvas *_canvas;
  bool _scrollable;
  QColor _color;
  QString _image_hash;
  int _image_mode;
};

#endif // SHEET_H
