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
  Q_PROPERTY(bool scrollable READ scrollable WRITE setScrollable NOTIFY scrollableChanged)
  Q_PROPERTY(QColor color READ color WRITE setColor NOTIFY colorChanged)
  Q_PROPERTY(QString imageSource READ imageSource NOTIFY imageSourceChanged)
  Q_PROPERTY(int imageMode READ imageMode WRITE setImageMode NOTIFY imageModeChanged)
public:
  explicit Sheet(QQuickItem *parent = 0);

  // ISheet
  virtual ISheetCanvas *canvas() override;

  SheetCanvas *canvasObj() { return _canvas; }
  bool scrollable() const { return _scrollable; }
  void setScrollable(bool scrollable);
  QColor color() const { return _color; }
  void setColor(QColor color);
  QString imageHash() const { return _image_hash; }
  QString imageSource() const;
  void setImageHash(const QString &image_hash);
  int imageMode() const { return _image_mode; }
  void setImageMode(int image_mode);
  void serialize(QXmlStreamWriter *writer, QSet<QString> *brd_objects = nullptr);
  void deserialize(QXmlStreamReader *reader);
public slots:
  void copySettings(Sheet *sheet);
  void selectImage(const QUrl &file_url);
  void deleteImage();
signals:
  void scrollableChanged();
  void colorChanged();
  void imageSourceChanged();
  void imageModeChanged();
protected:
  virtual void componentComplete() override;
private:
  SheetCanvas *_canvas;
  bool _scrollable;
  QColor _color;
  QString _image_hash;
  int _image_mode;
};

#endif // SHEET_H
