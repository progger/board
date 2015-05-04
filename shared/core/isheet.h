/*
 * Copyright (C) 2012 Michael Kulabuhov, Kemerovo, Russia.
 *
 * See the LICENSE file for terms of use.
 */

#ifndef ISHEET_H
#define ISHEET_H

#include "isheetcanvas.h"

class ISheet {
public:
  virtual ~ISheet() {}
  virtual ISheetCanvas *canvas() = 0;
  virtual bool scrollable() = 0;
  virtual QColor color() = 0;
  virtual QString imageHash() = 0;
  virtual QString imageSource() = 0;
  virtual int imageMode() = 0;
public slots:
  virtual void setScrollable(bool scrollable) = 0;
  virtual void setColor(QColor color) = 0;
  virtual void setImageHash(const QString &image_hash) = 0;
  virtual void setImageMode(int image_mode) = 0;
signals:
  virtual void scrollableChanged() = 0;
  virtual void colorChanged() = 0;
  virtual void imageSourceChanged() = 0;
  virtual void imageModeChanged() = 0;
};

Q_DECLARE_INTERFACE(ISheet, "board.core.ISheet")

#endif // ISHEET_H
