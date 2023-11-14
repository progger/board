/*
 * Copyright (C) 2014 Michael Kulabuhov, Kemerovo, Russia.
 *
 * See the LICENSE file for terms of use.
 */

#ifndef CARDTRANSFORM_H
#define CARDTRANSFORM_H

#include "shape.h"
#include "card.h"

class CardTransform : public Shape
{
  Q_OBJECT
  Q_DISABLE_COPY_MOVE(CardTransform)
  Q_PROPERTY(QQmlListProperty<Card> cards READ cardsProperty NOTIFY cardsChanged)
public:
  explicit CardTransform(QQuickItem *parent = nullptr);
  ~CardTransform() override = default;
  QList<Card*> *cards() { return &_cards; }
  QQmlListProperty<Card> cardsProperty();
signals:
  void cardsChanged();
public slots:
  void generate();
  void addItem();
  void removeItem(int index);
  void setCardLeftImage(int index, const QUrl &file_url);
  void setCardRightImage(int index, const QUrl &file_url);
  void saveItems();
protected:
  QString elementName() const override;
  void innerSerialize(QXmlStreamWriter *writer, QSet<QString> *brd_objects) const override;
  void innerDeserialize(QXmlStreamReader *reader) override;
private:
  QList<Card*> _cards;
  QString _hash;
};

#endif // CARDTRANSFORM_H
