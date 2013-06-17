/*
 * Copyright (C) 2012 Michael Kulabuhov, Kemerovo, Russia.
 *
 * See the LICENSE file for terms of use.
 */

#ifndef ISHEETCANVAS_H
#define ISHEETCANVAS_H

#include <QQuickItem>

class ISheetCanvas {
public:
  virtual ~ISheetCanvas() {}
  virtual QQuickItem *container() = 0;
  virtual QPointF sheetPoint() = 0;
  virtual QRectF sheetRect() = 0;
  virtual QSizeF canvasSize() = 0;
  virtual void pushState() = 0;
  virtual void updateSheetRect() = 0;
};

Q_DECLARE_INTERFACE(ISheetCanvas, "board.core.ISheetCanvas/2.0")

#endif // ISHEETCANVAS_H
