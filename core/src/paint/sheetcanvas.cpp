/*
 * Copyright (C) 2013 Kulabuhov Michael, Kemerovo, Russia.
 *
 * See the LICENSE file for terms of use.
 */

#include <QCursor>
#include <QQmlEngine>
#include "../core.h"
#include "paint.h"
#include "selectgen.h"
#include "pengen.h"
#include "magicpengen.h"
#include "rectanglegen.h"
#include "circlegen.h"
#include "ellipsegen.h"
#include "textgen.h"
#include "imagegen.h"
#include "sheetcanvas.h"

using namespace std;

SheetCanvas::SheetCanvas(QQuickItem *parent) :
  QQuickItem(parent),
  _shape_gen(nullptr),
  _start_move(false)
{
  connect(this, SIGNAL(enabledChanged()), SLOT(onEnabledChanged()));
}

void SheetCanvas::setCore(Core *core)
{
  _core = core;
}

void SheetCanvas::setPaint(Paint *paint)
{
  _paint = paint;
  connect(_paint, SIGNAL(modeChanged()), SLOT(onModeChanged()));
}

void SheetCanvas::onEnabledChanged()
{
  if (isEnabled())
  {
    if (_paint->mode() == "image")
      _paint->setMode("select");
    else
      onModeChanged();
  }
  else
  {
    _shape_gen = nullptr;
  }
}

void SheetCanvas::onModeChanged()
{
  if (!isEnabled()) return;
  _shape_gen = nullptr;
  QString mode = _paint->mode();
  if (mode == "select")
  {
    _shape_gen = make_shared<SelectGen>(this);
  }
  else if (mode == "pen")
  {
    _shape_gen = make_shared<PenGen>(this);
  }
  else if (mode == "magic_pen")
  {
    _shape_gen = make_shared<MagicPenGen>(this);
  }
  else if (mode == "rectangle")
  {
    _shape_gen = make_shared<RectangleGen>(this);
  }
  else if (mode == "circle")
  {
    _shape_gen = make_shared<CircleGen>(this);
  }
  else if (mode == "ellipse")
  {
    _shape_gen = make_shared<EllipseGen>(this);
  }
  else if (mode == "text")
  {
    _shape_gen = make_shared<TextGen>(this);
  }
  else if (mode == "image")
  {
    _shape_gen = ImageGen::openFile(this);
    if (!_shape_gen)
      _paint->setMode("select");
  }
}

void SheetCanvas::onMousePress(QObject *event)
{
  if (!_shape_gen) return;
  QPointF p(event->property("x").toInt(), event->property("y").toInt());
  _shape_gen->begin(p);
  _start_move = true;
}

void SheetCanvas::onMouseRelease(QObject *event)
{
  if (!_shape_gen) return;
  QPointF p(event->property("x").toInt(), event->property("y").toInt());
  _shape_gen->end(p);
  _start_move = false;
}

void SheetCanvas::onMouseMove(QObject *event)
{
  if (!_shape_gen || !_start_move) return;
  QPointF p(event->property("x").toInt(), event->property("y").toInt());
  _shape_gen->move(p);
}

void SheetCanvas::componentComplete()
{
  QQuickItem::componentComplete();
  _container = findChild<QQuickItem*>("container");
  Q_ASSERT(_container);
  _select_rect = findChild<QQuickItem*>("selectRect");
  Q_ASSERT(_select_rect);
  _text_input = findChild<QQuickItem*>("textInput");
  Q_ASSERT(_select_rect);

  QQuickView *view = qobject_cast<QQuickView*>(_core->mainView());
  QQmlEngine *engine = view->engine();
  _comp_text_wrapper = shared_ptr<QQmlComponent>(new QQmlComponent(engine, QUrl("qrc:/core/qml/TextWrapper.qml")));
  Q_ASSERT(_comp_text_wrapper);
  _comp_image_wrapper = shared_ptr<QQmlComponent>(new QQmlComponent(engine, QUrl("qrc:/core/qml/ImageWrapper.qml")));
  Q_ASSERT(_comp_image_wrapper);
}
