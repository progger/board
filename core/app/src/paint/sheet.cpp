/*
 * Copyright (C) 2013 Kulabuhov Michael, Kemerovo, Russia.
 *
 * See the LICENSE file for terms of use.
 */

#include "sheet.h"

Sheet::Sheet(QQuickItem *parent) :
  QQuickItem(parent)
{
}

void Sheet::componentComplete()
{
  QQuickItem::componentComplete();
  _sheet_canvas = findChild<SheetCanvas*>("sheetCanvas");
  Q_ASSERT(_sheet_canvas);
}
