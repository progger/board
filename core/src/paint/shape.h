/*
 * Copyright (C) 2013 Kulabuhov Michael, Kemerovo, Russia.
 *
 * See the LICENSE file for terms of use.
 */

#ifndef SHAPE_H
#define SHAPE_H

#include <QQuickItem>

class Shape : public QQuickItem
{
  Q_OBJECT
  Q_PROPERTY(int thickness READ thickness WRITE setThickness NOTIFY thicknessChanged)
  Q_PROPERTY(QColor color READ color WRITE setColor NOTIFY colorChanged)
  Q_PROPERTY(qreal scalex READ scalex NOTIFY scalexChanged)
  Q_PROPERTY(qreal scaley READ scaley NOTIFY scaleyChanged)
public:
  explicit Shape(QQuickItem *parent = 0);
  explicit Shape(QQuickItem *parent, float thickness, QColor color);
  QSizeF innerSize() const { return _inner_size; }
  void setInnerSize(const QSizeF &size) { _inner_size = size; }
  qreal scalex() const;
  qreal scaley() const;
  int thickness() const { return _thickness; }
  QColor color() const { return _color; }
public slots:
  void setThickness(int thickness);
  void setColor(const QColor &color);
  void onWidthChanged();
  void onHeightChanged();
signals:
  void thicknessChanged();
  void colorChanged();
  void scalexChanged();
  void scaleyChanged();
protected:
  float _thickness;
  QColor _color;
  QSizeF _inner_size;
};

#endif // SHAPE_H
