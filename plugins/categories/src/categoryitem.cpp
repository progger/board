/*
 * Copyright (C) 2014 Michael Kulabuhov, Kemerovo, Russia.
 *
 * See the LICENSE file for terms of use.
 */

#include "global.h"
#include "categoryitem.h"

CategoryItem::CategoryItem(QObject *parent) :
  QObject(parent),
  _category(),
  _hash()
{
}

QString CategoryItem::source() const
{
  return g_core->brdStore()->getUrlString(_hash);
}

void CategoryItem::setCategory(Category *category)
{
  _category = category;
  emit categoryChanged();
}

void CategoryItem::setHash(const QString &hash)
{
  _hash = hash;
  emit hashChanged();
}
