/*
 * Copyright (C) 2013 Michael Kulabuhov, Kemerovo, Russia.
 *
 * See the LICENSE file for terms of use.
 */

#ifndef SHAPE_H
#define SHAPE_H

#include <QSet>
#include <QXmlStreamWriter>
#include <QXmlStreamReader>
#include <QQuickItem>
#include "isheetcanvas.h"

class Shape : public QQuickItem
{
  Q_OBJECT
  Q_DISABLE_COPY_MOVE(Shape)
  Q_PROPERTY(QSizeF innerSize READ innerSize WRITE setInnerSize NOTIFY innerSizeChanged)
  Q_PROPERTY(qreal thickness READ thickness WRITE setThickness NOTIFY thicknessChanged)
  Q_PROPERTY(QColor color READ color WRITE setColor NOTIFY colorChanged)
  Q_PROPERTY(QColor bgcolor READ bgcolor WRITE setBgcolor NOTIFY bgcolorChanged)
  Q_PROPERTY(bool locked READ locked WRITE setLocked NOTIFY lockedChanged)
  Q_PROPERTY(qreal scalex READ scalex NOTIFY scalexChanged)
  Q_PROPERTY(qreal scaley READ scaley NOTIFY scaleyChanged)
public:
  explicit Shape(QQuickItem *parent = nullptr, float thickness = 0, QColor color = QColor(),
                 QColor bgcolor = QColor(Qt::transparent));
  ~Shape() override = default;
  virtual void init(ISheetCanvas *canvas);
  ISheetCanvas *canvas() const { return _canvas; }
  void serialize(QXmlStreamWriter *writer, QSet<QString> *brd_objects = nullptr) const;
  void deserialize(QXmlStreamReader *reader);
  QSizeF innerSize() const { return _inner_size; }
  qreal scalex() const;
  qreal scaley() const;
  qreal thickness() const { return _thickness; }
  QColor color() const { return _color; }
  QColor bgcolor() const { return _bgcolor; }
  bool locked() const { return _locked; }
  virtual bool checkIntersect(const QRectF &rect);
public slots:
  void setInnerSize(const QSizeF &size);
  void setThickness(qreal thickness);
  void setColor(const QColor &color);
  void setBgcolor(const QColor &bgcolor);
  void setLocked(bool locked);
signals:
  void innerSizeChanged();
  void thicknessChanged();
  void colorChanged();
  void bgcolorChanged();
  void lockedChanged();
  void scalexChanged();
  void scaleyChanged();
protected:
  virtual QString elementName() const = 0;
  virtual void innerSerialize(QXmlStreamWriter *writer, QSet<QString> *brd_objects) const;
  virtual void innerDeserialize(QXmlStreamReader *reader);
private slots:
  void onWidthChanged();
  void onHeightChanged();
private:
  ISheetCanvas *_canvas;
  QSizeF _inner_size;
  qreal _thickness;
  QColor _color;
  QColor _bgcolor;
  bool _locked;
};

#endif // SHAPE_H
