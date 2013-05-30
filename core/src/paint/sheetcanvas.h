/*
 * Copyright (C) 2013 Kulabuhov Michael, Kemerovo, Russia.
 *
 * See the LICENSE file for terms of use.
 */

#ifndef SHEETCANVAS_H
#define SHEETCANVAS_H

#include <memory>
#include <set>
#include <QXmlStreamWriter>
#include <QXmlStreamReader>
#include <QQuickItem>

class Core;
class Paint;
class Shape;
class ShapeGen;
class StrStack;

class SheetCanvas : public QQuickItem
{
  Q_OBJECT
  Q_PROPERTY(Core* core READ core WRITE setCore NOTIFY coreChanged)
  Q_PROPERTY(QPointF sheetPoint READ sheetPoint NOTIFY sheetPointChanged)
  Q_PROPERTY(QRectF sheetRect READ sheetRect NOTIFY sheetRectChanged)
public:
  explicit SheetCanvas(QQuickItem *parent = 0);
  Core *core() const { return _core; }
  Paint *paint() const { return _paint; }
  QPointF sheetPoint() const { return _sheet_point; }
  QRectF sheetRect() const { return _sheet_rect; }
  Q_INVOKABLE void moveSheet(qreal dx, qreal dy);
  QQuickItem *container() const { return _container; }
  QQuickItem *selectRect() const { return _select_rect; }
  QQuickItem *textInput() const { return _text_input; }
  void serializeSheet(QXmlStreamWriter *writer, std::set<QString> *brd_objects = nullptr);
  void deserializeSheet(QXmlStreamReader *reader);
  void deserializeShapes(QXmlStreamReader *reader, std::vector<Shape*> *shapes = nullptr);
  void pushState();
public slots:
  void setCore(Core *core);
  void updateSheetRect();
  void onEnabledChanged();
  void onModeChanged();
  void onMousePress(QObject *event);
  void onMouseRelease(QObject *event);
  void onMouseMove(QObject *event);
  void onUndo();
  void onRedo();
signals:
  void coreChanged();
  void sheetPointChanged();
  void sheetRectChanged();
protected:
  virtual void componentComplete() override;
  virtual void geometryChanged(const QRectF &newGeometry, const QRectF &oldGeometry) override;
private:
  Core *_core;
  Paint *_paint;
  QPointF _sheet_point;
  QRectF _sheet_rect;
  QQuickItem *_container;
  QQuickItem *_select_rect;
  QQuickItem *_text_input;
  std::shared_ptr<ShapeGen> _shape_gen;
  std::shared_ptr<StrStack> _undo_stack;
  std::shared_ptr<StrStack> _redo_stack;
  QByteArray _cur_state;
  bool _start_move;
};

#endif // SHEETCANVAS_H
