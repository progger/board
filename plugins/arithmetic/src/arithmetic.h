/*
 * Copyright (C) 2014 Michael Kulabuhov, Kemerovo, Russia.
 *
 * See the LICENSE file for terms of use.
 */

#ifndef ARITHMETIC_H
#define ARITHMETIC_H

#include <vector>
#include "shape.h"
#include "arithmeticitem.h"

class Arithmetic : public Shape
{
  Q_OBJECT
  Q_PROPERTY(QQmlListProperty<ArithmeticItem> items READ itemsProperty NOTIFY itemsChanged)
public:
  explicit Arithmetic(QQuickItem *parent = 0);
  std::vector<ArithmeticItem*> *items() { return &_items; }
  QQmlListProperty<ArithmeticItem> itemsProperty();
signals:
  void itemsChanged();
public slots:
  void generate();
  void addItem();
  void removeItem(int index);
  void saveItems();
protected:
  virtual QString elementName() const override;
  virtual void innerSerialize(QXmlStreamWriter *writer, std::set<QString> *brd_objects) const override;
  virtual void innerDeserialize(QXmlStreamReader *reader) override;
private:
  std::vector<ArithmeticItem*> _items;
  QString _hash;
};

#endif // ARITHMETIC_H
