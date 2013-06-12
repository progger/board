/*
 * Copyright (C) 2013 Kulabuhov Michael, Kemerovo, Russia.
 *
 * See the LICENSE file for terms of use.
 */

#include <QCursor>
#include "global.h"
#include "../core.h"
#include "../str_stack/strstack.h"
#include "paint.h"
#include "shape.h"
#include "shapegen.h"
#include "sheetcanvas.h"

using namespace std;

SheetCanvas::SheetCanvas(QQuickItem *parent) :
  QQuickItem(parent),
  _sheet_point(),
  _sheet_rect(0, 0, 1, 1),
  _shape_gen(nullptr),
  _undo_stack(make_shared<StrStack>()),
  _redo_stack(make_shared<StrStack>()),
  _cur_state(),
  _start_move(false)
{
  connect(this, SIGNAL(enabledChanged()), SLOT(onEnabledChanged()));
  Core *core = static_cast<Core*>(g_core);
  _paint = core->paintObj();
  connect(_paint, SIGNAL(modeChanged()), SLOT(onModeChanged()));
  connect(_paint, SIGNAL(undo()), SLOT(onUndo()));
  connect(_paint, SIGNAL(redo()), SLOT(onRedo()));
}

QQuickItem *SheetCanvas::container()
{
  return _container;
}

void SheetCanvas::moveSheet(qreal dx, qreal dy)
{
  QPointF dp(dx, dy);
  for (QQuickItem *item : _container->childItems())
  {
    item->setPosition(item->position() - dp);
  }
  _sheet_point += dp;
  updateSheetRect();
  emit sheetPointChanged();
}

void SheetCanvas::serializeSheet(QXmlStreamWriter *writer, set<QString> *brd_objects)
{
  writer->writeStartElement("sheet");
  for (QQuickItem *item : _container->childItems())
  {
    Shape *shape = qobject_cast<Shape*>(item);
    if (shape)
    {
      shape->serialize(writer, this, brd_objects);
    }
  }
  writer->writeEndElement();
}

void SheetCanvas::deserializeSheet(QXmlStreamReader *reader)
{
  for (QQuickItem *item : _container->childItems())
  {
    delete item;
  }
  if (reader->tokenType() != QXmlStreamReader::StartElement || reader->name() != "sheet") return;
  deserializeShapes(reader);
}

void SheetCanvas::deserializeShapes(QXmlStreamReader *reader, std::vector<Shape*> *shapes)
{
  while (reader->readNextStartElement())
  {
    QString name = reader->name().toString();
    Shape *shape = _paint->createShape(name);
    if (shape)
    {
      shape->setParent(_container);
      shape->setParentItem(_container);
      shape->deserialize(reader, this);
      if (shapes)
      {
        shapes->push_back(shape);
      }
    }
    else
    {
      while (true)
      {
        auto token = reader->readNext();
        if (token == QXmlStreamReader::Invalid) return;
        if (token == QXmlStreamReader::EndElement && reader->name() == name) break;
      }
    }
  }
}

void SheetCanvas::pushState()
{
  QByteArray data;
  QXmlStreamWriter writer(&data);
  serializeSheet(&writer);
  if (data != _cur_state)
  {
    _undo_stack->push(_cur_state);
    _redo_stack->clear();
    _cur_state = data;
    _paint->setCanUndo(true);
    _paint->setCanRedo(false);
  }
}

void SheetCanvas::updateSheetRect()
{
  if (!_container) return;
  qreal w = width();
  qreal h = height();
  qreal x1 = 0;
  qreal y1 = 0;
  qreal x2 = w;
  qreal y2 = h;
  for (QQuickItem *item : _container->childItems())
  {
    x1 = qMin(x1, item->x() - w);
    y1 = qMin(y1, item->y() - h);
    x2 = qMax(x2, item->x() + item->width() + w);
    y2 = qMax(y2, item->y() + item->height() + h);
  }
  _sheet_rect = QRectF(x1, y1, qMax(x2 - x1, 1.0), qMax(y2 - y1, 1.0));
  emit sheetRectChanged();
}

void SheetCanvas::onEnabledChanged()
{
  if (isEnabled())
  {
    onModeChanged();
    _paint->setCanUndo(!_undo_stack->empty());
    _paint->setCanRedo(!_redo_stack->empty());
  }
  else
  {
    _shape_gen = nullptr;
  }
}

void SheetCanvas::onModeChanged()
{
  if (!isEnabled()) return;
  _shape_gen = _paint->createShapeGen(this);
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

void SheetCanvas::onUndo()
{
  if (!isEnabled()) return;
  _redo_stack->push(_cur_state);
  _cur_state = _undo_stack->pop();
  QXmlStreamReader reader(_cur_state);
  reader.readNextStartElement();
  deserializeSheet(&reader);
  _paint->setCanUndo(!_undo_stack->empty());
  _paint->setCanRedo(true);
  _shape_gen = _paint->createShapeGen(this);
  updateSheetRect();
}

void SheetCanvas::onRedo()
{
  if (!isEnabled()) return;
  _undo_stack->push(_cur_state);
  _cur_state = _redo_stack->pop();
  QXmlStreamReader reader(_cur_state);
  reader.readNextStartElement();
  deserializeSheet(&reader);
  _paint->setCanUndo(true);
  _paint->setCanRedo(!_redo_stack->empty());
  _shape_gen = _paint->createShapeGen(this);
  updateSheetRect();
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

  updateSheetRect();
}

void SheetCanvas::geometryChanged(const QRectF &newGeometry, const QRectF &oldGeometry)
{
  QQuickItem::geometryChanged(newGeometry, oldGeometry);
  updateSheetRect();
}

QPointF SheetCanvas::sheetPoint()
{
  return _sheet_point;
}

QRectF SheetCanvas::sheetRect()
{
  return _sheet_rect;
}

QSizeF SheetCanvas::canvasSize()
{
  return QSizeF(width(), height());
}
