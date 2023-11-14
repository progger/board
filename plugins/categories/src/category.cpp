/*
 * Copyright (C) 2014 Michael Kulabuhov, Kemerovo, Russia.
 *
 * See the LICENSE file for terms of use.
 */

#include "category.h"

Category::Category(QObject *parent) :
  QObject(parent),
  _name(),
  _items()
{
}

QQmlListProperty<CategoryItem> Category::itemsProperty()
{
  return {this, nullptr,
    [](QQmlListProperty<CategoryItem> *list) -> int
    {
      auto *category = qobject_cast<Category*>(list->object);
      Q_ASSERT(category);
      return category->items()->size();
    },
    [](QQmlListProperty<CategoryItem> *list, int index) -> CategoryItem*
    {
      auto *category = qobject_cast<Category*>(list->object);
      Q_ASSERT(category);
      return category->items()->at(index);
    }};
}

void Category::setName(const QString &name)
{
  _name = name;
  emit nameChanged();
}

void Category::addItem(CategoryItem *item)
{
  _items.append(item);
  emit itemsChanged();
}

void Category::removeItem(CategoryItem *item)
{
  if (_items.removeOne(item))
  {
    emit itemsChanged();
  }
}

void Category::clearItems()
{
  _items.clear();
  emit itemsChanged();
}
