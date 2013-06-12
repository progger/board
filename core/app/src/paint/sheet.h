/*
 * Copyright (C) 2013 Kulabuhov Michael, Kemerovo, Russia.
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
public:
  explicit Sheet(QQuickItem *parent = 0);

  // ISheet
  virtual ISheetCanvas *canvas() override;

  SheetCanvas *canvasObj() { return _canvas; }
protected:
  virtual void componentComplete() override;
private:
  SheetCanvas *_canvas;
};

#endif // SHEET_H
