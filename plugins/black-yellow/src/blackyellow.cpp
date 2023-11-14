/*
 * Copyright (C) 2014 Michael Kulabuhov, Kemerovo, Russia.
 *
 * See the LICENSE file for terms of use.
 */

#include "global.h"
#include "blackyellow.h"

BlackYellow::BlackYellow(QQuickItem *parent) :
  Shape(parent),
  _items(),
  _hash()
{
}

QQmlListProperty<BlackYellowItem> BlackYellow::itemsProperty()
{
  return {this, nullptr,
    [](QQmlListProperty<BlackYellowItem> *list) -> int
    {
      auto *black_yellow = qobject_cast<BlackYellow*>(list->object);
      Q_ASSERT(black_yellow);
      return black_yellow->items()->size();
    },
    [](QQmlListProperty<BlackYellowItem> *list, int index) -> BlackYellowItem*
    {
      auto *black_yellow = qobject_cast<BlackYellow*>(list->object);
      Q_ASSERT(black_yellow);
      return black_yellow->items()->at(index);
    }};
}

void BlackYellow::addItem()
{
  auto *item = new BlackYellowItem(this);
  item->setQuestion("Вопрос");
  item->setAnswer("Ответ");
  _items.append(item);
  saveItems();
  emit itemsChanged();
}

void BlackYellow::removeItem(int index)
{
  _items[index]->deleteLater();
  _items.removeAt(index);
  saveItems();
  emit itemsChanged();
}

void BlackYellow::saveItems()
{
  QStringList list;
  for (BlackYellowItem *item : _items)
  {
    list.append(item->question());
    list.append(item->answer());
  }
  QByteArray data = list.join('|').toUtf8();
  _hash = g_core->brdStore()->addObject(data);
  canvas()->pushState();
}

QString BlackYellow::elementName() const
{
  return "black-yellow";
}

void BlackYellow::innerSerialize(QXmlStreamWriter *writer, QSet<QString> *brd_objects) const
{
  Shape::innerSerialize(writer, brd_objects);
  writer->writeAttribute("version", QString::number(1));
  writer->writeAttribute("hash", _hash);
  if (brd_objects) brd_objects->insert(_hash);
}

void BlackYellow::innerDeserialize(QXmlStreamReader *reader)
{
  Shape::innerDeserialize(reader);
  for (BlackYellowItem *item : _items)
  {
    item->deleteLater();
  }
  _items.clear();
  _hash = reader->attributes().value("hash").toString();
  QByteArray data = g_core->brdStore()->getObject(_hash);
  QStringList list = QString::fromUtf8(data).split('|');
  int count = list.size() / 2;
  for (int i = 0; i < count; ++i)
  {
    auto *item = new BlackYellowItem(this);
    item->setQuestion(list[i * 2]);
    item->setAnswer(list[i * 2 + 1]);
    _items.append(item);
  }
  emit itemsChanged();
}
