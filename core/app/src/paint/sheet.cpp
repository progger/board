/*
 * Copyright (C) 2013 Michael Kulabuhov, Kemerovo, Russia.
 *
 * See the LICENSE file for terms of use.
 */

#include "sheet.h"

Sheet::Sheet(QQuickItem *parent) :
  QQuickItem(parent)
{
}

ISheetCanvas *Sheet::canvas()
{
  return _canvas;
}

void Sheet::componentComplete()
{
  QQuickItem::componentComplete();
  _canvas = findChild<SheetCanvas*>("sheetCanvas");
  Q_ASSERT(_canvas);
}
