/*
 * Copyright (C) 2014 Michael Kulabuhov, Kemerovo, Russia.
 *
 * See the LICENSE file for terms of use.
 */

#include <algorithm>
#include "global.h"
#include "cardtransform.h"

CardTransform::CardTransform(QQuickItem *parent) :
  Shape(parent),
  _cards(),
  _hash()
{
}

QQmlListProperty<Card> CardTransform::cardsProperty()
{
  return QQmlListProperty<Card>(this, nullptr,
    [](QQmlListProperty<Card> *list) -> int
    {
      CardTransform *transform = qobject_cast<CardTransform*>(list->object);
      Q_ASSERT(transform);
      return transform->cards()->size();
    },
    [](QQmlListProperty<Card> *list, int index) -> Card*
    {
  CardTransform *transform = qobject_cast<CardTransform*>(list->object);
  Q_ASSERT(transform);
      return transform->cards()->at(index);
});
}

void CardTransform::generate()
{
  addItem();
  saveItems();
  emit cardsChanged();
}

void CardTransform::addItem()
{
  Card *card = new Card(this);
  QString file_name = QString(":/transform/res/cardX.svg");
  card->setLeftHash(g_core->brdStore()->addFromFile(file_name));
  file_name = QString(":/transform/res/cardY.svg");
  card->setRightHash(g_core->brdStore()->addFromFile(file_name));
  _cards.append(card);
  saveItems();
  emit cardsChanged();
}

void CardTransform::removeItem(int index)
{
  _cards[index]->deleteLater();
  _cards.removeAt(index);
  saveItems();
  emit cardsChanged();
}

void CardTransform::setCardLeftImage(int index, const QUrl &file_url)
{
  QString hash = g_core->brdStore()->addFromUrl(file_url);
  _cards[index]->setLeftHash(hash);
  saveItems();
}

void CardTransform::setCardRightImage(int index, const QUrl &file_url)
{
  QString hash = g_core->brdStore()->addFromUrl(file_url);
  _cards[index]->setRightHash(hash);
  saveItems();
}

void CardTransform::saveItems()
{
  QStringList list;
  for (Card *card : _cards)
  {
    list.append(card->leftHash());
    list.append(card->rightHash());
  }
  QByteArray data = list.join('|').toUtf8();
  _hash = g_core->brdStore()->addObject(data);
  canvas()->pushState();
}

QString CardTransform::elementName() const
{
  return "transform";
}

void CardTransform::innerSerialize(QXmlStreamWriter *writer, QSet<QString> *brd_objects) const
{
  Shape::innerSerialize(writer, brd_objects);
  writer->writeAttribute("version", QString::number(1));
  writer->writeAttribute("hash", _hash);
  if (brd_objects)
  {
    brd_objects->insert(_hash);
    for (Card *card : _cards)
    {
      brd_objects->insert(card->leftHash());
      brd_objects->insert(card->rightHash());
    }
  }
}

void CardTransform::innerDeserialize(QXmlStreamReader *reader)
{
  Shape::innerDeserialize(reader);
  for (Card *card : _cards)
  {
    card->deleteLater();
  }
  _cards.clear();
  _hash = reader->attributes().value("hash").toString();
  QByteArray data = g_core->brdStore()->getObject(_hash);
  QStringList list = QString::fromUtf8(data).split('|');
  int count = list.size() / 2;
  for (int i = 0; i < count; ++i)
  {
    Card *card = new Card(this);
    card->setLeftHash(list[i * 2]);
    card->setRightHash(list[i * 2 + 1]);
    _cards.append(card);
  }
  emit cardsChanged();
}
