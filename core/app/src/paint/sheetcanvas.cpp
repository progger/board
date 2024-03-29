/*
 * Copyright (C) 2013 Michael Kulabuhov, Kemerovo, Russia.
 *
 * See the LICENSE file for terms of use.
 */

#include "global.h"
#include "../core.h"
#include "paint.h"
#include "shape.h"
#include "shapegen.h"
#include "sheetcanvas.h"

SheetCanvas::SheetCanvas(QQuickItem *parent) :
  QQuickItem(parent),
  _zoom(1),
  _sheet_rect(0, 0, 1, 1),
  _container(),
  _select_rect(),
  _text_input(),
  _shape_gen(),
  _undo_stack(),
  _redo_stack(),
  _cur_state(),
  _start_move(),
  _z_min(0),
  _z_max(-1),
  _mouse_x(0),
  _mouse_y(0),
  _contains_mouse(false)
{
  Core *core = static_cast<Core*>(g_core);
  _paint = core->paintObj();
  setAcceptedMouseButtons(Qt::LeftButton);
  setAcceptHoverEvents(true);
  connect(this, SIGNAL(enabledChanged()), SLOT(onEnabledChanged()));
  connect(_paint, SIGNAL(modeChanged()), SLOT(onModeChanged()));
  connect(_paint, SIGNAL(undo()), SLOT(onUndo()));
  connect(_paint, SIGNAL(redo()), SLOT(onRedo()));
}

QQuickItem *SheetCanvas::container()
{
  return _container;
}

qreal SheetCanvas::zoom()
{
  return _zoom;
}

QRectF SheetCanvas::sheetRect()
{
  return _sheet_rect;
}

QRectF SheetCanvas::viewRect()
{
  return mapRectToItem(_container, QRectF(0, 0, width(), height()));
}

qreal SheetCanvas::getZMin()
{
  return _z_min;
}

qreal SheetCanvas::getZMax()
{
  return _z_max;
}

qreal SheetCanvas::getZNext()
{
  return _z_max + 1;
}

void SheetCanvas::setZoom(qreal zoom)
{
  _zoom = zoom;
  emit zoomChanged();
  updateSheetRect();
  emit viewRectChanged();
}

void SheetCanvas::setViewPoint(qreal x, qreal y)
{
  _container->setPosition(QPointF(-x * _zoom, -y * _zoom));
  emit viewRectChanged();
}

void SheetCanvas::pushState()
{
  QByteArray data;
  QXmlStreamWriter writer(&data);
  writer.writeStartElement("sheet");
  serialize(&writer);
  writer.writeEndElement();
  if (data != _cur_state)
  {
    _undo_stack.push(_cur_state);
    _redo_stack.clear();
    _cur_state = data;
    _paint->setCanUndo(true);
    _paint->setCanRedo(false);
  }
  updateZMinMax();
  g_core->setChanges();
}

void SheetCanvas::updateSheetRect()
{
  if (!_container) return;
  QPointF p1 = mapToItem(_container, QPointF(0, 0));
  QPointF p2 = mapToItem(_container, QPointF(width(), height()));
  qreal w = p2.x() - p1.x();
  qreal h = p2.y() - p1.y();
  qreal x1 = p1.x();
  qreal y1 = p1.y();
  qreal x2 = p2.x();
  qreal y2 = p2.y();
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

void SheetCanvas::moveSheet(qreal dx, qreal dy)
{
  QPointF dp(dx * _zoom, dy * _zoom);
  _container->setPosition(_container->position() + dp);
  updateSheetRect();
  emit viewRectChanged();
}

void SheetCanvas::serialize(QXmlStreamWriter *writer, QSet<QString> *brd_objects)
{
  for (QQuickItem *item : _container->childItems())
  {
    auto *shape = qobject_cast<Shape*>(item);
    if (shape)
    {
      shape->serialize(writer, brd_objects);
    }
  }
}

void SheetCanvas::deserialize(QXmlStreamReader *reader)
{
  for (QQuickItem *item : _container->childItems())
  {
    delete item;
  }
  deserializeShapes(reader);
}

void SheetCanvas::deserializeShapes(QXmlStreamReader *reader, QList<Shape*> *shapes)
{
  while (reader->readNextStartElement())
  {
    QString name = reader->name().toString();
    Shape *shape = _paint->createShape(name, this);
    if (shape)
    {
      shape->deserialize(reader);
      if (shapes)
      {
        shapes->append(shape);
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
  updateSheetRect();
}

void SheetCanvas::onEnabledChanged()
{
  if (isEnabled())
  {
    _paint->setCanUndo(!_undo_stack.empty());
    _paint->setCanRedo(!_redo_stack.empty());
  }
  else
  {
    _shape_gen.clear();
    _start_move.clear();
  }
  setCursor(_paint->getCursor());
}

void SheetCanvas::onModeChanged()
{
  if (!isEnabled()) return;
  _shape_gen.clear();
  setCursor(_paint->getCursor());
}

void SheetCanvas::onUndo()
{
  if (!isEnabled()) return;
  _redo_stack.push(_cur_state);
  _cur_state = _undo_stack.pop();
  QXmlStreamReader reader(_cur_state);
  reader.readNextStartElement();
  deserialize(&reader);
  _paint->setCanUndo(!_undo_stack.empty());
  _paint->setCanRedo(true);
  _shape_gen.clear();
  _start_move.clear();
  updateSheetRect();
  updateZMinMax();
  g_core->setChanges();
}

void SheetCanvas::onRedo()
{
  if (!isEnabled()) return;
  _undo_stack.push(_cur_state);
  _cur_state = _redo_stack.pop();
  QXmlStreamReader reader(_cur_state);
  reader.readNextStartElement();
  deserialize(&reader);
  _paint->setCanUndo(true);
  _paint->setCanRedo(!_redo_stack.empty());
  _shape_gen.clear();
  _start_move.clear();
  updateSheetRect();
  updateZMinMax();
  g_core->setChanges();
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

void SheetCanvas::mousePressEvent(QMouseEvent *event)
{
  if (!isEnabled()) return;
  quint16 id = event->modifiers() & 0xffff;
  auto shape_gen = getShapeGen(id);
  QPointF p(event->x(), event->y());
  p = mapToItem(_container, p);
  shape_gen->begin(p);
  _start_move.insert(id);
}

void SheetCanvas::mouseReleaseEvent(QMouseEvent *event)
{
  if (!isEnabled()) return;
  quint16 id = event->modifiers() & 0xffff;
  auto shape_gen = getShapeGen(id);
  QPointF p(event->x(), event->y());
  p = mapToItem(_container, p);
  shape_gen->end(p);
  _start_move.remove(id);
}

void SheetCanvas::mouseMoveEvent(QMouseEvent *event)
{
  if (!isEnabled()) return;
  _mouse_x = event->x();
  _mouse_y = event->y();
  emit mousePositionChanged();
  quint16 id = event->modifiers() & 0xffff;
  if (!_start_move.contains(id)) return;
  auto shape_gen = getShapeGen(id);
  QPointF p(event->x(), event->y());
  p = mapToItem(_container, p);
  shape_gen->move(p);
}

void SheetCanvas::hoverEnterEvent(QHoverEvent *)
{
  _contains_mouse = true;
  emit containsMouseChanged();
}

void SheetCanvas::hoverLeaveEvent(QHoverEvent *)
{
  _contains_mouse = false;
  emit containsMouseChanged();
}

void SheetCanvas::hoverMoveEvent(QHoverEvent *event)
{
  _mouse_x = event->pos().x();
  _mouse_y = event->pos().y();
  emit mousePositionChanged();
}

void SheetCanvas::updateZMinMax()
{
  _z_min = 0;
  _z_max = -1;
  for (QQuickItem *item : _container->childItems())
  {
    qreal z = item->z();
    if (z < _z_min) _z_min = z;
    if (z > _z_max) _z_max = z;
  }
}

QSharedPointer<ShapeGen> SheetCanvas::getShapeGen(int id)
{
  QSharedPointer<ShapeGen> &shape_gen = _shape_gen[id];
  if (!shape_gen)
  {
    shape_gen = _paint->createShapeGen(this);
  }
  return shape_gen;
}
