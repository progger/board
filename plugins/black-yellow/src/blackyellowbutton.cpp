/*
 * Copyright (C) 2014 Michael Kulabuhov, Kemerovo, Russia.
 *
 * See the LICENSE file for terms of use.
 */

#include "global.h"
#include "isheet.h"
#include "blackyellow.h"
#include "blackyellowbutton.h"

BlackYellowButton::BlackYellowButton(QQuickItem *parent) :
  QQuickItem(parent)
{
}

void BlackYellowButton::placeBlackYellow()
{
  ISheet *sheet = g_core->sheet(g_core->sheetIndex());
  ISheetCanvas *canvas = sheet->canvas();
  auto *black_yellow = qobject_cast<BlackYellow*>(g_core->paint()->createShape("black-yellow", canvas));
  Q_ASSERT(black_yellow);
  QRectF viewRect = canvas->viewRect();
  QSizeF size = QSizeF(viewRect.width() * 0.75, viewRect.height() * 0.85);
  black_yellow->setPosition(QPointF(viewRect.x() + (viewRect.width() - size.width()) / 2,
                                    viewRect.y() + (viewRect.height() - size.height()) / 2));
  black_yellow->setSize(size);
  black_yellow->addItem();
  black_yellow->saveItems();
  canvas->updateSheetRect();
}
