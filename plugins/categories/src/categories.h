/*
 * Copyright (C) 2014 Michael Kulabuhov, Kemerovo, Russia.
 *
 * See the LICENSE file for terms of use.
 */

#ifndef CATEGORIES_H
#define CATEGORIES_H

#include "shape.h"
#include "category.h"

class Categories : public Shape
{
  Q_OBJECT
  Q_DISABLE_COPY_MOVE(Categories)
  Q_PROPERTY(QQmlListProperty<Category> categories READ categoriesProperty NOTIFY categoriesChanged)
  Q_PROPERTY(QQmlListProperty<CategoryItem> items READ itemsProperty NOTIFY itemsChanged)
  Q_PROPERTY(QQmlListProperty<CategoryItem> remainingItems READ remainingItemsProperty NOTIFY remainingItemsChanged)
public:
  explicit Categories(QQuickItem *parent = nullptr);
  ~Categories() override = default;
  QList<Category*> *categories() { return &_categories; }
  QQmlListProperty<Category> categoriesProperty();
  QList<CategoryItem*> *items() { return &_items; }
  QQmlListProperty<CategoryItem> itemsProperty();
  QList<CategoryItem*> *remainingItems() { return &_remaining_items; }
  QQmlListProperty<CategoryItem> remainingItemsProperty();
  Q_INVOKABLE bool checkResult() const;
signals:
  void categoriesChanged();
  void itemsChanged();
  void remainingItemsChanged();
public slots:
  void generate();
  void shuffle();
  void addCategory();
  void removeCategory(Category *category);
  void addItem(Category *category, const QUrl &file_url);
  void removeItem(CategoryItem *item);
  void updateRemainingItems();
  void clearCategoriesItems();
  void fillCategoriesItems();
  void saveItems();
protected:
  QString elementName() const override;
  void innerSerialize(QXmlStreamWriter *writer, QSet<QString> *brd_objects) const override;
  void innerDeserialize(QXmlStreamReader *reader) override;
private:
  QList<Category*> _categories;
  QList<CategoryItem*> _items;
  QList<CategoryItem*> _remaining_items;
  QString _hash;
};

#endif // CATEGORIES_H
