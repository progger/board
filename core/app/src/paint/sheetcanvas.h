/*
 * Copyright (C) 2013 Michael Kulabuhov, Kemerovo, Russia.
 *
 * See the LICENSE file for terms of use.
 */

#ifndef SHEETCANVAS_H
#define SHEETCANVAS_H

#include <QSet>
#include <QMap>
#include <QSharedPointer>
#include <QXmlStreamWriter>
#include <QXmlStreamReader>
#include <QQuickItem>
#include "../str_stack/strstack.h"
#include "isheetcanvas.h"

class Paint;
class Shape;
class ShapeGen;

class SheetCanvas : public QQuickItem, public ISheetCanvas
{
  Q_OBJECT
  Q_INTERFACES(ISheetCanvas)
  Q_PROPERTY(QPointF sheetPoint READ sheetPoint NOTIFY sheetPointChanged)
  Q_PROPERTY(QRectF sheetRect READ sheetRect NOTIFY sheetRectChanged)
  Q_PROPERTY(int mouseX READ mouseX NOTIFY mousePositionChanged)
  Q_PROPERTY(int mouseY READ mouseY NOTIFY mousePositionChanged)
  Q_PROPERTY(bool containsMouse READ containsMouse NOTIFY containsMouseChanged)
public:
  explicit SheetCanvas(QQuickItem *parent = 0);

  // ISheetCanvas
  virtual QQuickItem *container() override;
  virtual QPointF sheetPoint() override;
  virtual QRectF sheetRect() override;
  virtual QSizeF canvasSize() override;
  virtual void pushState() override;
  virtual void updateSheetRect() override;
  virtual qreal getZMin() override;
  virtual qreal getZMax() override;
  virtual qreal getZNext() override;

  Paint *paintObj() const { return _paint; }
  Q_INVOKABLE void moveSheet(qreal dx, qreal dy);
  QQuickItem *selectRect() const { return _select_rect; }
  QQuickItem *textInput() const { return _text_input; }
  void serialize(QXmlStreamWriter *writer, QSet<QString> *brd_objects = nullptr);
  void deserialize(QXmlStreamReader *reader);
  void deserializeShapes(QXmlStreamReader *reader, QList<Shape*> *shapes = nullptr);
  int mouseX() { return _mouse_x; }
  int mouseY() { return _mouse_y; }
  bool containsMouse() { return _contains_mouse; }
public slots:
  void onEnabledChanged();
  void onScaleChanged();
  void onModeChanged();
  void onUndo();
  void onRedo();
signals:
  void sheetPointChanged();
  void sheetRectChanged();
  void mousePositionChanged();
  void containsMouseChanged();
protected:
  virtual void componentComplete() override;
  virtual void geometryChanged(const QRectF &newGeometry, const QRectF &oldGeometry) override;
  virtual void mousePressEvent(QMouseEvent *event) override;
  virtual void mouseReleaseEvent(QMouseEvent *event) override;
  virtual void mouseMoveEvent(QMouseEvent *event) override;
  virtual void hoverEnterEvent(QHoverEvent *) override;
  virtual void hoverLeaveEvent(QHoverEvent *) override;
  virtual void hoverMoveEvent(QHoverEvent *event) override;
private:
  Paint *_paint;
  QPointF _sheet_point;
  QRectF _sheet_rect;
  QQuickItem *_container;
  QQuickItem *_select_rect;
  QQuickItem *_text_input;
  QMap<quint16, QSharedPointer<ShapeGen>> _shape_gen;
  StrStack _undo_stack;
  StrStack _redo_stack;
  QByteArray _cur_state;
  QSet<quint16> _start_move;
  qreal _z_min;
  qreal _z_max;
  int _mouse_x;
  int _mouse_y;
  bool _contains_mouse;
  void updateZMinMax();
  QSharedPointer<ShapeGen> getShapeGen(int id);
};

#endif // SHEETCANVAS_H
