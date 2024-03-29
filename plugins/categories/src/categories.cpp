/*
 * Copyright (C) 2014 Michael Kulabuhov, Kemerovo, Russia.
 *
 * See the LICENSE file for terms of use.
 */

#include <algorithm>
#include <QRandomGenerator>
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
  return {this, nullptr,
    [](QQmlListProperty<Category> *list) -> int
    {
      auto *categories = qobject_cast<Categories*>(list->object);
      Q_ASSERT(categories);
      return categories->categories()->size();
    },
    [](QQmlListProperty<Category> *list, int index) -> Category*
    {
      auto *categories = qobject_cast<Categories*>(list->object);
      Q_ASSERT(categories);
      return categories->categories()->at(index);
    }};
}

QQmlListProperty<CategoryItem> Categories::itemsProperty()
{
  return {this, nullptr,
    [](QQmlListProperty<CategoryItem> *list) -> int
    {
      auto *categories = qobject_cast<Categories*>(list->object);
      Q_ASSERT(categories);
      return categories->items()->size();
    },
    [](QQmlListProperty<CategoryItem> *list, int index) -> CategoryItem*
    {
      auto *categories = qobject_cast<Categories*>(list->object);
      Q_ASSERT(categories);
      return categories->items()->at(index);
    }};
}

QQmlListProperty<CategoryItem> Categories::remainingItemsProperty()
{
  return {this, nullptr,
    [](QQmlListProperty<CategoryItem> *list) -> int
    {
      auto *categories = qobject_cast<Categories*>(list->object);
      Q_ASSERT(categories);
      return categories->remainingItems()->size();
    },
    [](QQmlListProperty<CategoryItem> *list, int index) -> CategoryItem*
    {
      auto *categories = qobject_cast<Categories*>(list->object);
      Q_ASSERT(categories);
      return categories->remainingItems()->at(index);
    }};
}

bool Categories::checkResult() const
{
  if (!_remaining_items.empty()) return false;
  for (auto *category : _categories)
  {
    for (auto *item : *category->items())
    {
      if (item->category() != category) return false;
    }
  }
  return true;
}

void Categories::generate()
{
  auto *cat1 = new Category(this);
  cat1->setName("Чётные числа");
  _categories.append(cat1);
  auto *cat2 = new Category(this);
  cat2->setName("Нечётные числа");
  _categories.append(cat2);
  for (int i = 1; i <= 8; ++i)
  {
    auto file_name = QString(":/categories/res/card%1.svg").arg(i);
    auto hash = g_core->brdStore()->addFromFile(file_name);
    auto *item = new CategoryItem(this);
    item->setHash(hash);
    if (i % 2)
      item->setCategory(cat2);
    else
      item->setCategory(cat1);
    _items.append(item);
  }
  updateRemainingItems();
  shuffle();
  saveItems();
  emit itemsChanged();
  emit categoriesChanged();
}

void Categories::shuffle()
{
  auto *rng = QRandomGenerator::global();
  int count = _remaining_items.size();
  for (int i = 0; i < count; ++i)
  {
    _remaining_items.swapItemsAt(i, rng->bounded(count));
  }
  emit remainingItemsChanged();
}

void Categories::addCategory()
{
  auto *category = new Category(this);
  category->setName("Новая категория");
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
      category->removeItem(item);
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

void Categories::addItem(Category *category, const QUrl &file_url)
{
  QString file_name = file_url.toLocalFile();
  QString hash = g_core->brdStore()->addFromFile(file_name);
  if (hash.isEmpty()) return;
  auto *item = new CategoryItem(this);
  item->setHash(hash);
  item->setCategory(category);
  _items.append(item);
  saveItems();
  updateRemainingItems();
  emit itemsChanged();
}

void Categories::removeItem(CategoryItem *item)
{
  item->deleteLater();
  for (Category *category : _categories)
  {
    category->removeItem(item);
  }
  _items.removeOne(item);
  saveItems();
  updateRemainingItems();
  emit itemsChanged();
}

void Categories::updateRemainingItems()
{
  for (CategoryItem *item : _items)
  {
    if (!_remaining_items.contains(item))
    {
      _remaining_items.append(item);
    }
  }
  for (Category *category : _categories)
  {
    for (CategoryItem *item : *category->items())
    {
      _remaining_items.removeOne(item);
    }
  }
  emit remainingItemsChanged();
}

void Categories::clearCategoriesItems()
{
  for (Category *category : _categories)
  {
    category->clearItems();
  }
  updateRemainingItems();
}

void Categories::fillCategoriesItems()
{
  clearCategoriesItems();
  for (CategoryItem *item : _items)
  {
    item->category()->addItem(item);
  }
  updateRemainingItems();
}

void Categories::saveItems()
{
  QByteArray data;
  QTextStream stream(&data, QIODevice::WriteOnly);
  for (Category *category : _categories)
  {
    stream << category->name() << Qt::endl;
    QStringList list;
    for (CategoryItem *item : _items)
    {
      if (item->category() == category)
      {
        list.append(item->hash());
      }
    }
    stream << list.join(" ") << Qt::endl;
  }
  _hash = g_core->brdStore()->addObject(data);
  canvas()->pushState();
}

QString Categories::elementName() const
{
  return "categories";
}

void Categories::innerSerialize(QXmlStreamWriter *writer, QSet<QString> *brd_objects) const
{
  Shape::innerSerialize(writer, brd_objects);
  writer->writeAttribute("version", QString::number(1));
  writer->writeAttribute("hash", _hash);
  if (brd_objects)
  {
    brd_objects->insert(_hash);
    for (CategoryItem *item : _items)
    {
      brd_objects->insert(item->hash());
    }
  }
}

void Categories::innerDeserialize(QXmlStreamReader *reader)
{
  Shape::innerDeserialize(reader);
  for (Category *category : _categories)
  {
    category->deleteLater();
  }
  for (CategoryItem *item : _items)
  {
    item->deleteLater();
  }
  _categories.clear();
  _items.clear();
  _hash = reader->attributes().value("hash").toString();
  QByteArray data = g_core->brdStore()->getObject(_hash);
  QTextStream stream(data);
  while (!stream.atEnd())
  {
    auto *cat = new Category(this);
    cat->setName(stream.readLine());
    _categories.append(cat);
    auto line = stream.readLine();
    auto hashes = line.split(" ", Qt::SkipEmptyParts);
    for (const auto &hash : hashes)
    {
      auto *item = new CategoryItem(this);
      item->setCategory(cat);
      item->setHash(hash);
      _items.append(item);
    }
  }
  updateRemainingItems();
  shuffle();
  emit itemsChanged();
  emit categoriesChanged();
}
