/*
 * Copyright (C) 2013 Kulabuhov Michael, Kemerovo, Russia.
 *
 * See the LICENSE file for terms of use.
 */

#ifndef SHEETCANVAS_H
#define SHEETCANVAS_H

#include <QQuickItem>
#include <memory>

class Core;
class Paint;
class Shape;
class ShapeGen;

class SheetCanvas : public QQuickItem
{
  Q_OBJECT
  Q_PROPERTY(Core* core READ core WRITE setCore)
  Q_PROPERTY(Paint* paint READ paint WRITE setPaint)
public:
  explicit SheetCanvas(QQuickItem *parent = 0);
  Core *core() const { return _core; }
  Paint *paint() const { return _paint; }
  QQuickItem *container() const { return _container; }
  QQuickItem *selectRect() const { return _select_rect; }
  QQuickItem *textInput() const { return _text_input; }
  std::shared_ptr<QQmlComponent> compTextWrapper() const { return _comp_text_wrapper; }
public slots:
  void setCore(Core *core);
  void setPaint(Paint *paint);
  void onEnabledChanged();
  void onUpdateMode();
  void onMousePress(QObject *event);
  void onMouseRelease(QObject *event);
  void onMouseMove(QObject *event);
protected:
  virtual void componentComplete() override;
private:
  Core *_core;
  Paint *_paint;
  QQuickItem *_container;
  QQuickItem *_select_rect;
  QQuickItem *_text_input;
  std::shared_ptr<ShapeGen> _shape_gen;
  std::shared_ptr<QQmlComponent> _comp_text_wrapper;
  bool _start_move;
};

#endif // SHEETCANVAS_H
