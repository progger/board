/*
 * Copyright (C) 2014 Michael Kulabuhov, Kemerovo, Russia.
 *
 * See the LICENSE file for terms of use.
 */

#include "arithmetic.h"

Arithmetic::Arithmetic(QQuickItem *parent) :
  Shape(parent),
  _items()
{
}

QQmlListProperty<ArithmeticItem> Arithmetic::itemsProperty()
{
  return QQmlListProperty<ArithmeticItem>(this, nullptr,
    [](QQmlListProperty<ArithmeticItem> *list) -> int
    {
      Arithmetic *arithmetic = qobject_cast<Arithmetic*>(list->object);
      Q_ASSERT(arithmetic);
      return arithmetic->items()->size();
    },
    [](QQmlListProperty<ArithmeticItem> *list, int index) -> ArithmeticItem*
    {
      Arithmetic *arithmetic = qobject_cast<Arithmetic*>(list->object);
      Q_ASSERT(arithmetic);
      return arithmetic->items()->at(index);
    });
}

void Arithmetic::generate()
{
  while (_items.size() < 5)
  {
    _items.push_back(new ArithmeticItem(this));
  }
  for (auto item : _items)
  {
    item->generate();
  }
  emit itemsChanged();
}

QString Arithmetic::elementName() const
{
  return "arithmetic";
}
