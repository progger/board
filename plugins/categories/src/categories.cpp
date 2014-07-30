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
  for (int i = 1; i <= 8; ++i)
  {
    QString file_name = QString(":/categories/res/card%1.svg").arg(i);
    QString hash = g_core->brdStore()->addFromFile(file_name);
    CategoryItem *item = new CategoryItem(this);
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
  int count = _remaining_items.size();
  for (int i = 0; i < count; ++i)
  {
    _remaining_items.swap(i, qrand() % count);
  }
  emit remainingItemsChanged();
}

void Categories::addCategory()
{
  Category *category = new Category(this);
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
  CategoryItem *item = new CategoryItem(this);
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
    stream << category->name() << endl;
    QStringList list;
    for (CategoryItem *item : _items)
    {
      if (item->category() == category)
      {
        list.append(item->hash());
      }
    }
    stream << list.join(" ") << endl;
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
    Category *cat = new Category(this);
    cat->setName(stream.readLine());
    _categories.append(cat);
    QString line = stream.readLine();
    QStringList hashes = line.split(" ", QString::SkipEmptyParts);
    for (QString hash : hashes)
    {
      CategoryItem *item = new CategoryItem(this);
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
