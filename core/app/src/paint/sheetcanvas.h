/*
 * Copyright (C) 2013 Michael Kulabuhov, Kemerovo, Russia.
 *
 * See the LICENSE file for terms of use.
 */

#ifndef SHEETCANVAS_H
#define SHEETCANVAS_H

#include <QSet>
#include <QMap>
#include <QStack>
#include <QSharedPointer>
#include <QXmlStreamWriter>
#include <QXmlStreamReader>
#include <QQuickItem>
#include "isheetcanvas.h"

class Paint;
class Shape;
class ShapeGen;

class SheetCanvas : public QQuickItem, public ISheetCanvas
{
  Q_OBJECT
  Q_INTERFACES(ISheetCanvas)
  Q_DISABLE_COPY_MOVE(SheetCanvas)
  Q_PROPERTY(float zoom READ zoom WRITE setZoom NOTIFY zoomChanged)
  Q_PROPERTY(QRectF viewRect READ viewRect NOTIFY viewRectChanged)
  Q_PROPERTY(QRectF sheetRect READ sheetRect NOTIFY sheetRectChanged)
  Q_PROPERTY(int mouseX READ mouseX NOTIFY mousePositionChanged)
  Q_PROPERTY(int mouseY READ mouseY NOTIFY mousePositionChanged)
  Q_PROPERTY(bool containsMouse READ containsMouse NOTIFY containsMouseChanged)
public:
  explicit SheetCanvas(QQuickItem *parent = nullptr);
  ~SheetCanvas() override = default;

  // ISheetCanvas
public:
  QQuickItem *container() override;
  qreal zoom() override;
  QRectF sheetRect() override;
  QRectF viewRect() override;
  qreal getZMin() override;
  qreal getZMax() override;
  qreal getZNext() override;
public slots:
  void setZoom(qreal zoom) override;
  void setViewPoint(qreal x, qreal y) override;
  void pushState() override;
  void updateSheetRect() override;
signals:
  void zoomChanged() override;
  void viewRectChanged() override;

public:
  Paint *paintObj() const { return _paint; }
  Q_INVOKABLE void moveSheet(qreal dx, qreal dy);
  QQuickItem *selectRect() const { return _select_rect; }
  QQuickItem *textInput() const { return _text_input; }
  void serialize(QXmlStreamWriter *writer, QSet<QString> *brd_objects = nullptr);
  void deserialize(QXmlStreamReader *reader);
  void deserializeShapes(QXmlStreamReader *reader, QList<Shape*> *shapes = nullptr);
  int mouseX() const { return _mouse_x; }
  int mouseY() const { return _mouse_y; }
  bool containsMouse() const { return _contains_mouse; }
public slots:
  void onEnabledChanged();
  void onModeChanged();
  void onUndo();
  void onRedo();
signals:
  void sheetRectChanged();
  void mousePositionChanged();
  void containsMouseChanged();
protected:
  void componentComplete() override;
  void geometryChanged(const QRectF &newGeometry, const QRectF &oldGeometry) override;
  void mousePressEvent(QMouseEvent *event) override;
  void mouseReleaseEvent(QMouseEvent *event) override;
  void mouseMoveEvent(QMouseEvent *event) override;
  void hoverEnterEvent(QHoverEvent *) override;
  void hoverLeaveEvent(QHoverEvent *) override;
  void hoverMoveEvent(QHoverEvent *event) override;
private:
  Paint *_paint;
  qreal _zoom;
  QRectF _sheet_rect;
  QQuickItem *_container;
  QQuickItem *_select_rect;
  QQuickItem *_text_input;
  QMap<quint16, QSharedPointer<ShapeGen>> _shape_gen;
  QStack<QByteArray> _undo_stack;
  QStack<QByteArray> _redo_stack;
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
