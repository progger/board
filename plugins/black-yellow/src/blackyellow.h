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
  Q_PROPERTY(QQmlListProperty<BlackYellowItem> items READ itemsProperty NOTIFY itemsChanged)
public:
  explicit BlackYellow(QQuickItem *parent = 0);
  QList<BlackYellowItem*> *items() { return &_items; }
  QQmlListProperty<BlackYellowItem> itemsProperty();
signals:
  void itemsChanged();
public slots:
  void addItem();
  void removeItem(int index);
  void saveItems();
protected:
  virtual QString elementName() const override;
  virtual void innerSerialize(QXmlStreamWriter *writer, std::set<QString> *brd_objects) const override;
  virtual void innerDeserialize(QXmlStreamReader *reader) override;
private:
  QList<BlackYellowItem*> _items;
  QString _hash;
};

#endif // BLACKYELLOW_H
