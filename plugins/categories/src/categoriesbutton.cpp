/*
 * Copyright (C) 2014 Michael Kulabuhov, Kemerovo, Russia.
 *
 * See the LICENSE file for terms of use.
 */

#include "global.h"
#include "isheet.h"
#include "categories.h"
#include "categoriesbutton.h"

CategoriesButton::CategoriesButton(QQuickItem *parent) :
  QQuickItem(parent)
{
}

void CategoriesButton::placeCategories()
{
  ISheet *sheet = g_core->sheet(g_core->sheetIndex());
  ISheetCanvas *canvas = sheet->canvas();
  Categories *categories = qobject_cast<Categories*>(g_core->paint()->createShape("categories", canvas));
  Q_ASSERT(categories);
  QRectF viewRect = canvas->viewRect();
  QSizeF size = QSizeF(viewRect.width() * 0.75, viewRect.height() * 0.85);
  categories->setPosition(QPointF(viewRect.x() + (viewRect.width() - size.width()) / 2,
                                  viewRect.y() + (viewRect.height() - size.height()) / 2));
  categories->setSize(size);
  categories->generate();
  canvas->updateSheetRect();
}
