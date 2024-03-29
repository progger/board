/*
 * Copyright (C) 2014 Michael Kulabuhov, Kemerovo, Russia.
 *
 * See the LICENSE file for terms of use.
 */

#include "global.h"
#include "arithmetic.h"

Arithmetic::Arithmetic(QQuickItem *parent) :
  Shape(parent),
  _items(),
  _hash()
{
}

QQmlListProperty<ArithmeticItem> Arithmetic::itemsProperty()
{
  return {this, nullptr,
    [](QQmlListProperty<ArithmeticItem> *list) -> int
    {
      auto *arithmetic = qobject_cast<Arithmetic*>(list->object);
      Q_ASSERT(arithmetic);
      return arithmetic->items().size();
    },
    [](QQmlListProperty<ArithmeticItem> *list, int index) -> ArithmeticItem*
    {
      auto *arithmetic = qobject_cast<Arithmetic*>(list->object);
      Q_ASSERT(arithmetic);
      return arithmetic->items().at(index);
    }};
}

void Arithmetic::generate()
{
  while (_items.size() < 5)
  {
    _items.append(new ArithmeticItem(this));
  }
  for (auto *item : _items)
  {
    item->generate();
  }
  emit itemsChanged();
}

void Arithmetic::addItem()
{
  auto *item = new ArithmeticItem(this);
  item->generate();
  _items.append(item);
  saveItems();
  emit itemsChanged();
}

void Arithmetic::removeItem(int index)
{
  _items[index]->deleteLater();
  _items.erase(_items.begin() + index);
  saveItems();
  emit itemsChanged();
}

void Arithmetic::saveItems()
{
  QByteArray data;
  QTextStream stream(&data, QIODevice::WriteOnly);
  for (ArithmeticItem *item : _items)
  {
    stream << item->left() << " " << item->operation() << " " << item->right() << Qt::endl;
  }
  _hash = g_core->brdStore()->addObject(data);
  canvas()->pushState();
}

QString Arithmetic::elementName() const
{
  return "arithmetic";
}

void Arithmetic::innerSerialize(QXmlStreamWriter *writer, QSet<QString> *brd_objects) const
{
  Shape::innerSerialize(writer, brd_objects);
  writer->writeAttribute("version", QString::number(1));
  writer->writeAttribute("hash", _hash);
  if (brd_objects) brd_objects->insert(_hash);
}

void Arithmetic::innerDeserialize(QXmlStreamReader *reader)
{
  Shape::innerDeserialize(reader);
  for (ArithmeticItem *item : _items)
  {
    item->deleteLater();
  }
  _items.clear();
  _hash = reader->attributes().value("hash").toString();
  QByteArray data = g_core->brdStore()->getObject(_hash);
  QTextStream stream(data);
  while (!stream.atEnd())
  {
    int left, right;
    QString operation;
    stream >> left >> operation >> right;
    stream.readLine();
    auto *item = new ArithmeticItem(this);
    item->setLeft(left);
    item->setRight(right);
    item->setOperation(operation);
    _items.append(item);
  }
  emit itemsChanged();
}
