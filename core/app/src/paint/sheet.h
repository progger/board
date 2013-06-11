/*
 * Copyright (C) 2013 Kulabuhov Michael, Kemerovo, Russia.
 *
 * See the LICENSE file for terms of use.
 */

#ifndef SHEET_H
#define SHEET_H

#include <QQuickItem>
#include "sheetcanvas.h"

class Sheet : public QQuickItem
{
  Q_OBJECT
public:
  explicit Sheet(QQuickItem *parent = 0);
  SheetCanvas *sheetCanvas() { return _sheet_canvas; }
protected:
  virtual void componentComplete() override;
private:
  SheetCanvas *_sheet_canvas;
};

#endif // SHEET_H
