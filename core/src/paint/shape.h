/*
 * Copyright (C) 2013 Kulabuhov Michael, Kemerovo, Russia.
 *
 * See the LICENSE file for terms of use.
 */

#ifndef SHAPE_H
#define SHAPE_H

#include <QXmlStreamWriter>
#include <QXmlStreamReader>
#include <QQuickItem>

class SheetCanvas;

class Shape : public QQuickItem
{
  Q_OBJECT
  Q_PROPERTY(QSizeF innerSize READ innerSize WRITE setInnerSize NOTIFY innerSizeChanged)
  Q_PROPERTY(int thickness READ thickness WRITE setThickness NOTIFY thicknessChanged)
  Q_PROPERTY(QColor color READ color WRITE setColor NOTIFY colorChanged)
  Q_PROPERTY(qreal scalex READ scalex NOTIFY scalexChanged)
  Q_PROPERTY(qreal scaley READ scaley NOTIFY scaleyChanged)
public:
  explicit Shape(QQuickItem *parent = 0, float thickness = 0, QColor color = QColor());
  void serialize(QXmlStreamWriter *writer, SheetCanvas *canvas) const;
  void deserialize(QXmlStreamReader *reader, SheetCanvas *canvas);
  QSizeF innerSize() const { return _inner_size; }
  qreal scalex() const;
  qreal scaley() const;
  int thickness() const { return _thickness; }
  QColor color() const { return _color; }
public slots:
  void setInnerSize(const QSizeF &size);
  void setThickness(int thickness);
  void setColor(const QColor &color);
  void onWidthChanged();
  void onHeightChanged();
signals:
  void innerSizeChanged();
  void thicknessChanged();
  void colorChanged();
  void scalexChanged();
  void scaleyChanged();
protected:
  virtual QString elementName() const = 0;
  virtual void innerSerialize(QXmlStreamWriter *, SheetCanvas *) const {}
  virtual void innerDeserialize(QXmlStreamReader *, SheetCanvas *) {}
private:
  QSizeF _inner_size;
  float _thickness;
  QColor _color;
};

#endif // SHAPE_H
