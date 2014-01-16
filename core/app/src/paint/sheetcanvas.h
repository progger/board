/*
 * Copyright (C) 2013 Michael Kulabuhov, Kemerovo, Russia.
 *
 * See the LICENSE file for terms of use.
 */

#ifndef SHEETCANVAS_H
#define SHEETCANVAS_H

#include <memory>
#include <set>
#include <map>
#include <QXmlStreamWriter>
#include <QXmlStreamReader>
#include <QQuickItem>
#include "isheetcanvas.h"

class Paint;
class Shape;
class ShapeGen;
class StrStack;

class SheetCanvas : public QQuickItem, public ISheetCanvas
{
  Q_OBJECT
  Q_INTERFACES(ISheetCanvas)
  Q_PROPERTY(QPointF sheetPoint READ sheetPoint NOTIFY sheetPointChanged)
  Q_PROPERTY(QRectF sheetRect READ sheetRect NOTIFY sheetRectChanged)
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
  void serializeSheet(QXmlStreamWriter *writer, std::set<QString> *brd_objects = nullptr);
  void deserializeSheet(QXmlStreamReader *reader);
  void deserializeShapes(QXmlStreamReader *reader, std::vector<Shape*> *shapes = nullptr);
public slots:
  void onEnabledChanged();
  void onModeChanged();
  void onUndo();
  void onRedo();
signals:
  void sheetPointChanged();
  void sheetRectChanged();
protected:
  virtual void componentComplete() override;
  virtual void geometryChanged(const QRectF &newGeometry, const QRectF &oldGeometry) override;
  virtual void mousePressEvent(QMouseEvent *event) override;
  virtual void mouseReleaseEvent(QMouseEvent *event) override;
  virtual void mouseMoveEvent(QMouseEvent *event) override;
private:
  Paint *_paint;
  QPointF _sheet_point;
  QRectF _sheet_rect;
  QQuickItem *_container;
  QQuickItem *_select_rect;
  QQuickItem *_text_input;
  std::map<quint16, std::shared_ptr<ShapeGen>> _shape_gen;
  std::shared_ptr<StrStack> _undo_stack;
  std::shared_ptr<StrStack> _redo_stack;
  QByteArray _cur_state;
  std::set<quint16> _start_move;
  qreal _z_min;
  qreal _z_max;
  void updateZMinMax();
  std::shared_ptr<ShapeGen> getShapeGen(int id);
};

#endif // SHEETCANVAS_H
