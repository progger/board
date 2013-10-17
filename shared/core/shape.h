/*
 * Copyright (C) 2013 Michael Kulabuhov, Kemerovo, Russia.
 *
 * See the LICENSE file for terms of use.
 */

#ifndef SHAPE_H
#define SHAPE_H

#include <set>
#include <QXmlStreamWriter>
#include <QXmlStreamReader>
#include <QQuickItem>
#include "isheetcanvas.h"

class Shape : public QQuickItem
{
  Q_OBJECT
  Q_PROPERTY(QSizeF innerSize READ innerSize WRITE setInnerSize NOTIFY innerSizeChanged)
  Q_PROPERTY(int thickness READ thickness WRITE setThickness NOTIFY thicknessChanged)
  Q_PROPERTY(QColor color READ color WRITE setColor NOTIFY colorChanged)
  Q_PROPERTY(QColor background READ background WRITE setBackground NOTIFY backgroundChanged)
  Q_PROPERTY(qreal scalex READ scalex NOTIFY scalexChanged)
  Q_PROPERTY(qreal scaley READ scaley NOTIFY scaleyChanged)
public:
  explicit Shape(QQuickItem *parent = 0, float thickness = 0, QColor color = QColor(),
                 QColor background = QColor(Qt::transparent));
  void serialize(QXmlStreamWriter *writer, ISheetCanvas *canvas, std::set<QString> *brd_objects = nullptr) const;
  void deserialize(QXmlStreamReader *reader, ISheetCanvas *canvas);
  QSizeF innerSize() const { return _inner_size; }
  qreal scalex() const;
  qreal scaley() const;
  int thickness() const { return _thickness; }
  QColor color() const { return _color; }
  QColor background() const { return _background; }
  virtual bool checkIntersect(const QRectF &rect);
public slots:
  void setInnerSize(const QSizeF &size);
  void setThickness(int thickness);
  void setColor(const QColor &color);
  void setBackground(const QColor &background);
signals:
  void innerSizeChanged();
  void thicknessChanged();
  void colorChanged();
  void backgroundChanged();
  void scalexChanged();
  void scaleyChanged();
protected:
  virtual QString elementName() const = 0;
  virtual void innerSerialize(QXmlStreamWriter *, ISheetCanvas *, std::set<QString> *) const {}
  virtual void innerDeserialize(QXmlStreamReader *, ISheetCanvas *) {}
private slots:
  void onWidthChanged();
  void onHeightChanged();
private:
  QSizeF _inner_size;
  float _thickness;
  QColor _color;
  QColor _background;
};

#endif // SHAPE_H
