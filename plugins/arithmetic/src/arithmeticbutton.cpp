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
  Arithmetic *arithmetic = qobject_cast<Arithmetic*>(g_core->paint()->createShape("arithmetic"));
  Q_ASSERT(arithmetic);
  arithmetic->init(canvas);
  arithmetic->setZ(canvas->getZNext());
  QSizeF size = QSizeF(canvas->container()->width() / 2, canvas->container()->height() / 1.5);
  arithmetic->setPosition(QPointF((canvas->container()->width() - size.width()) / 2,
                                  (canvas->container()->height() - size.height()) / 2));
  arithmetic->setSize(size);
  arithmetic->generate();
  arithmetic->saveItems();
  canvas->updateSheetRect();
}
