/*
 * Copyright (C) 2014 Michael Kulabuhov, Kemerovo, Russia.
 *
 * See the LICENSE file for terms of use.
 */

#ifndef BLACKYELLOW_H
#define BLACKYELLOW_H

#include "shape.h"
#include "blackyellowitem.h"

class BlackYellow : public Shape
{
  Q_OBJECT
  Q_DISABLE_COPY_MOVE(BlackYellow)
  Q_PROPERTY(QQmlListProperty<BlackYellowItem> items READ itemsProperty NOTIFY itemsChanged)
public:
  explicit BlackYellow(QQuickItem *parent = nullptr);
  ~BlackYellow() override = default;
  QList<BlackYellowItem*> *items() { return &_items; }
  QQmlListProperty<BlackYellowItem> itemsProperty();
signals:
  void itemsChanged();
public slots:
  void addItem();
  void removeItem(int index);
  void saveItems();
protected:
  QString elementName() const override;
  void innerSerialize(QXmlStreamWriter *writer, QSet<QString> *brd_objects) const override;
  void innerDeserialize(QXmlStreamReader *reader) override;
private:
  QList<BlackYellowItem*> _items;
  QString _hash;
};

#endif // BLACKYELLOW_H
