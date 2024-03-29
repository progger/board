/*
 * Copyright (C) 2014 Michael Kulabuhov, Kemerovo, Russia.
 *
 * See the LICENSE file for terms of use.
 */

#include "global.h"
#include "isheet.h"
#include "arithmetic.h"
#include "arithmeticbutton.h"

ArithmeticButton::ArithmeticButton(QQuickItem *parent) :
  QQuickItem(parent)
{
}

void ArithmeticButton::placeArithmetic()
{
  ISheet *sheet = g_core->sheet(g_core->sheetIndex());
  ISheetCanvas *canvas = sheet->canvas();
  auto *arithmetic = qobject_cast<Arithmetic*>(g_core->paint()->createShape("arithmetic", canvas));
  Q_ASSERT(arithmetic);
  QRectF viewRect = canvas->viewRect();
  QSizeF size = QSizeF(viewRect.width() * 0.75, viewRect.height() * 0.85);
  arithmetic->setPosition(QPointF(viewRect.x() + (viewRect.width() - size.width()) / 2,
                                  viewRect.y() + (viewRect.height() - size.height()) / 2));
  arithmetic->setSize(size);
  arithmetic->generate();
  arithmetic->saveItems();
  canvas->updateSheetRect();
}
