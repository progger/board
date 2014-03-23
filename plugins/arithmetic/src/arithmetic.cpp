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

void Arithmetic::saveItems()
{
  QByteArray data;
  QTextStream stream(&data, QIODevice::WriteOnly);
  for (ArithmeticItem *item : _items)
  {
    stream << item->left() << " " << item->operation() << " " << item->right() << endl;
  }
  _hash = g_core->brdStore()->addObject(data);
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

void Arithmetic::addItem()
{
  ArithmeticItem *item = new ArithmeticItem(this);
  item->generate();
  _items.push_back(item);
  emit itemsChanged();
}

void Arithmetic::removeItem(int index)
{
  _items[index]->deleteLater();
  _items.erase(_items.begin() + index);
  emit itemsChanged();
}

QString Arithmetic::elementName() const
{
  return "arithmetic";
}

void Arithmetic::innerSerialize(QXmlStreamWriter *writer, ISheetCanvas *canvas, std::set<QString> *brd_objects) const
{
  Shape::innerSerialize(writer, canvas, brd_objects);
  writer->writeAttribute("hash", _hash);
  if (brd_objects) brd_objects->insert(_hash);
}

void Arithmetic::innerDeserialize(QXmlStreamReader *reader, ISheetCanvas *canvas)
{
  Shape::innerDeserialize(reader, canvas);
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
    ArithmeticItem *item = new ArithmeticItem(this);
    item->setLeft(left);
    item->setRight(right);
    item->setOperation(operation);
    _items.push_back(item);
  }
  _items.shrink_to_fit();
  emit itemsChanged();
}
