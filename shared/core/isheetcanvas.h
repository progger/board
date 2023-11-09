/*
 * Copyright (C) 2012 Michael Kulabuhov, Kemerovo, Russia.
 *
 * See the LICENSE file for terms of use.
 */

#ifndef ISHEETCANVAS_H
#define ISHEETCANVAS_H

#include <QQuickItem>

class ISheetCanvas {
  Q_DISABLE_COPY_MOVE(ISheetCanvas)
public:
  ISheetCanvas() = default;
  virtual ~ISheetCanvas() = default;
  virtual QQuickItem *container() = 0;
  virtual qreal zoom() = 0;
  virtual QRectF sheetRect() = 0;
  virtual QRectF viewRect() = 0;
  virtual qreal getZMin() = 0;
  virtual qreal getZMax() = 0;
  virtual qreal getZNext() = 0;
public slots:
  virtual void setZoom(qreal zoom) = 0;
  virtual void setViewPoint(qreal x, qreal y) = 0;
  virtual void pushState() = 0;
  virtual void updateSheetRect() = 0;
signals:
  virtual void zoomChanged() = 0;
  virtual void viewRectChanged() = 0;
};

Q_DECLARE_INTERFACE(ISheetCanvas, "board.core.ISheetCanvas")

#endif // ISHEETCANVAS_H
