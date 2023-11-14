/*
 * Copyright (C) 2014 Michael Kulabuhov, Kemerovo, Russia.
 *
 * See the LICENSE file for terms of use.
 */

#ifndef ARITHMETIC_H
#define ARITHMETIC_H

#include "shape.h"
#include "arithmeticitem.h"

class Arithmetic : public Shape
{
  Q_OBJECT
  Q_DISABLE_COPY_MOVE(Arithmetic)
  Q_PROPERTY(QQmlListProperty<ArithmeticItem> items READ itemsProperty NOTIFY itemsChanged)
public:
  explicit Arithmetic(QQuickItem *parent = nullptr);
  ~Arithmetic() override = default;
  QList<ArithmeticItem*> items() { return _items; }
  QQmlListProperty<ArithmeticItem> itemsProperty();
signals:
  void itemsChanged();
public slots:
  void generate();
  void addItem();
  void removeItem(int index);
  void saveItems();
protected:
  QString elementName() const override;
  void innerSerialize(QXmlStreamWriter *writer, QSet<QString> *brd_objects) const override;
  void innerDeserialize(QXmlStreamReader *reader) override;
private:
  QList<ArithmeticItem*> _items;
  QString _hash;
};

#endif // ARITHMETIC_H
