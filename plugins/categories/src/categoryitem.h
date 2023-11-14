/*
 * Copyright (C) 2014 Michael Kulabuhov, Kemerovo, Russia.
 *
 * See the LICENSE file for terms of use.
 */

#ifndef CATEGORYITEM_H
#define CATEGORYITEM_H

#include <QObject>

class Category;

class CategoryItem : public QObject
{
  Q_OBJECT
  Q_DISABLE_COPY_MOVE(CategoryItem)
  Q_PROPERTY(Category *category READ category WRITE setCategory NOTIFY categoryChanged)
  Q_PROPERTY(QString hash READ hash WRITE setHash NOTIFY hashChanged)
  Q_PROPERTY(QString source READ source NOTIFY hashChanged)
public:
  explicit CategoryItem(QObject *parent = nullptr);
  ~CategoryItem() override = default;
  Category *category() const { return _category; }
  QString hash() const { return _hash; }
  QString source() const;
signals:
  void categoryChanged();
  void hashChanged();
public slots:
  void setCategory(Category *category);
  void setHash(const QString &hash);
private:
  Category *_category;
  QString _hash;
};

#endif // CATEGORYITEM_H
