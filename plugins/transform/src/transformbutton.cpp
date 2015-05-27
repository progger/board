/*
 * Copyright (C) 2014 Michael Kulabuhov, Kemerovo, Russia.
 *
 * See the LICENSE file for terms of use.
 */

#include "global.h"
#include "isheet.h"
#include "cardtransform.h"
#include "transformbutton.h"

TransformButton::TransformButton(QQuickItem *parent) :
  QQuickItem(parent)
{
}

void TransformButton::placeTransform()
{
  ISheet *sheet = g_core->sheet(g_core->sheetIndex());
  ISheetCanvas *canvas = sheet->canvas();
  CardTransform *transform = qobject_cast<CardTransform*>(g_core->paint()->createShape("transform", canvas));
  Q_ASSERT(transform);
  QRectF viewRect = canvas->viewRect();
  QSizeF size = QSizeF(viewRect.width() * 0.75, viewRect.height() * 0.85);
  transform->setPosition(QPointF(viewRect.x() + (viewRect.width() - size.width()) / 2,
                                 viewRect.y() + (viewRect.height() - size.height()) / 2));
  transform->setSize(size);
  transform->generate();
  canvas->updateSheetRect();
}
