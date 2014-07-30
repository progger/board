/*
 * Copyright (C) 2014 Michael Kulabuhov, Kemerovo, Russia.
 *
 * See the LICENSE file for terms of use.
 */

#ifndef CATEGORY_H
#define CATEGORY_H

#include <QQmlListProperty>
#include "categoryitem.h"

class Category : public QObject
{
  Q_OBJECT
  Q_PROPERTY(QString name READ name WRITE setName NOTIFY nameChanged)
  Q_PROPERTY(QQmlListProperty<CategoryItem> items READ itemsProperty NOTIFY itemsChanged)
public:
  explicit Category(QObject *parent = 0);
  QString name() const { return _name; }
  QList<CategoryItem*> *items() { return &_items; }
  QQmlListProperty<CategoryItem> itemsProperty();
signals:
  void nameChanged();
  void itemsChanged();
public slots:
  void setName(const QString &name);
  void addItem(CategoryItem* item);
  void removeItem(CategoryItem *item);
  void clearItems();
private:
  QString _name;
  QList<CategoryItem*> _items;
};

#endif // CATEGORY_H
