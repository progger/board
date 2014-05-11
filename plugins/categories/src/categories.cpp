/*
 * Copyright (C) 2014 Michael Kulabuhov, Kemerovo, Russia.
 *
 * See the LICENSE file for terms of use.
 */

#include <algorithm>
#include "global.h"
#include "categories.h"

Categories::Categories(QQuickItem *parent) :
  Shape(parent),
  _categories(),
  _items(),
  _remaining_items(),
  _hash()
{
}

QQmlListProperty<Category> Categories::categoriesProperty()
{
  return QQmlListProperty<Category>(this, nullptr,
    [](QQmlListProperty<Category> *list) -> int
    {
      Categories *categories = qobject_cast<Categories*>(list->object);
      Q_ASSERT(categories);
      return categories->categories()->size();
    },
    [](QQmlListProperty<Category> *list, int index) -> Category*
    {
      Categories *categories = qobject_cast<Categories*>(list->object);
      Q_ASSERT(categories);
      return categories->categories()->at(index);
});
}

QQmlListProperty<CategoryItem> Categories::itemsProperty()
{
  return QQmlListProperty<CategoryItem>(this, nullptr,
    [](QQmlListProperty<CategoryItem> *list) -> int
    {
      Categories *categories = qobject_cast<Categories*>(list->object);
      Q_ASSERT(categories);
      return categories->items()->size();
    },
    [](QQmlListProperty<CategoryItem> *list, int index) -> CategoryItem*
    {
      Categories *categories = qobject_cast<Categories*>(list->object);
      Q_ASSERT(categories);
      return categories->items()->at(index);
    });
}

QQmlListProperty<CategoryItem> Categories::remainingItemsProperty()
{
  return QQmlListProperty<CategoryItem>(this, nullptr,
    [](QQmlListProperty<CategoryItem> *list) -> int
    {
      Categories *categories = qobject_cast<Categories*>(list->object);
      Q_ASSERT(categories);
      return categories->remainingItems()->size();
    },
    [](QQmlListProperty<CategoryItem> *list, int index) -> CategoryItem*
    {
      Categories *categories = qobject_cast<Categories*>(list->object);
      Q_ASSERT(categories);
      return categories->remainingItems()->at(index);
});
}

bool Categories::checkResult() const
{
  if (_remaining_items.size() > 0) return false;
  for (Category *category : _categories)
  {
    for (CategoryItem *item : *category->items())
    {
      if (item->category() != category) return false;
    }
  }
  return true;
}

void Categories::generate()
{
  Category *cat1 = new Category(this);
  cat1->setName("Чётные числа");
  _categories.append(cat1);
  Category *cat2 = new Category(this);
  cat2->setName("Нечётные числа");
  _categories.append(cat2);
  for (int i = 1; i <= 4; ++i)
  {
    QString file_name = QString(":/categories/res/card%1.svg").arg(i);
    QString hash = g_core->brdStore()->addFromFile(file_name);
    CategoryItem *item = new CategoryItem(this);
    item->setCategory(0);
    item->setHash(hash);
    if (i % 2)
      item->setCategory(cat2);
    else
      item->setCategory(cat1);
    _items.append(item);
  }
  shuffle();
  saveItems();
  emit itemsChanged();
  emit categoriesChanged();
}

void Categories::shuffle()
{
  int count = _items.size();
  for (int i = 0; i < count; ++i)
  {
    _items.swap(i, qrand() % count);
  }
  updateRemainingItems();
}

void Categories::addCategory()
{
  Category *category = new Category(this);
  _categories.append(category);
  saveItems();
  emit categoriesChanged();
}

void Categories::removeCategory(Category *category)
{
  int count = _items.size();
  for (int i = count - 1; i >= 0; --i)
  {
    CategoryItem *item = _items[i];
    if (item->category() == category)
    {
      item->deleteLater();
      _items.removeAt(i);
    }
  }
  category->deleteLater();
  _categories.removeOne(category);
  saveItems();
  updateRemainingItems();
  emit itemsChanged();
  emit categoriesChanged();
}

void Categories::addItem(const QString &hash)
{
  CategoryItem *item = new CategoryItem(this);
  item->setHash(hash);
  _items.append(item);
  saveItems();
  updateRemainingItems();
  emit itemsChanged();
}

void Categories::removeItem(CategoryItem *item)
{
  item->deleteLater();
  _items.removeOne(item);
  saveItems();
  updateRemainingItems();
  emit itemsChanged();
}

void Categories::updateRemainingItems()
{
  _remaining_items = _items;
  for (Category *category : _categories)
  {
    for (CategoryItem *item : *category->items())
    {
      _remaining_items.removeOne(item);
    }
  }
  emit remainingItemsChanged();
}

void Categories::saveItems()
{
  //
  canvas()->pushState();
}

QString Categories::elementName() const
{
  return "categories";
}
