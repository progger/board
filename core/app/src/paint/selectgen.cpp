/*
 * Copyright (C) 2013 Michael Kulabuhov, Kemerovo, Russia.
 *
 * See the LICENSE file for terms of use.
 */

#include "sheetcanvas.h"
#include "paint.h"
#include "shape.h"
#include "selectgen.h"

SelectGen::SelectGen(ISheetCanvas *canvas) :
  ShapeGen(canvas),
  _selected(),
  _mx1(0),
  _my1(0),
  _mx2(0),
  _my2(0)
{
  _canvas_obj = static_cast<SheetCanvas*>(canvas);
  _select_rect = _canvas_obj->selectRect();
  _select_rect->setProperty("selectGen", QVariant::fromValue<QObject*>(this));
  connect(_canvas_obj, SIGNAL(sheetPointChanged()), SLOT(onSheetPointChanged()));
  connect(_canvas_obj->paintObj(), SIGNAL(del()), SLOT(onDel()));
  connect(_canvas_obj->paintObj(), SIGNAL(duplicate()), SLOT(onDuplicate()));
}

SelectGen::~SelectGen()
{
  _select_rect->setVisible(false);
  _canvas_obj->paintObj()->setSelected(false);
}

void SelectGen::begin(const QPointF &p)
{
  ShapeGen::begin(p);
  _select_rect->setPosition(p);
  _select_rect->setSize(QSizeF(0, 0));
  _select_rect->setVisible(true);
  _select_rect->setProperty("bobberVisible", false);
  _selected.clear();
}

void SelectGen::end(const QPointF &p)
{
  move(p);
  QRectF select(_select_rect->x(), _select_rect->y(),_select_rect->width(), _select_rect->height());
  bool click = select.width() < 8 && select.height() < 8;
  auto items = _canvas->container()->childItems();
  auto it = items.cend();
  while (it != items.cbegin())
  {
    --it;
    Shape *shape = qobject_cast<Shape*>(*it);
    if (!shape) continue;
    if (shape->checkIntersect(select))
    {
      _selected.push_back(shape);
      if (click) break;
    }
  }
  if (_selected.empty())
  {
    _select_rect->setVisible(false);
    _canvas_obj->paintObj()->setSelected(false);
  }
  else
  {
    _select_rect->setProperty("bobberVisible", true);
    updateRoundRect();
    _canvas_obj->paintObj()->setSelected(true);
  }
}

void SelectGen::move(const QPointF &p)
{
  qreal x1 = qMin(_start.x(), p.x());
  qreal y1 = qMin(_start.y(), p.y());
  qreal x2 = qMax(_start.x(), p.x());
  qreal y2 = qMax(_start.y(), p.y());
  _select_rect->setPosition(QPointF(x1, y1));
  QSizeF size(x2 - x1, y2 - y1);
  _select_rect->setSize(size);
}

void SelectGen::onMoveBegin(int x, int y)
{
  _start = QPointF(x, y) + _select_rect->position();
}

void SelectGen::onMoveEnd()
{
  _canvas->pushState();
  _canvas->updateSheetRect();
}

void SelectGen::onMove(int x, int y)
{
  QPointF p = QPointF(x, y) + _select_rect->position();
  QPointF dp = p - _start;
  for (Shape *item : _selected)
  {
    item->setPosition(item->position() + dp);
  }
  _select_rect->setPosition(_select_rect->position() + dp);
  _start = p;
}

void SelectGen::onScaleBegin(int x, int y, int mx1, int my1, int mx2, int my2)
{
  _start = QPointF(x, y);
  _mx1 = mx1;
  _my1 = my1;
  _mx2 = mx2;
  _my2 = my2;
}

void SelectGen::onScaleEnd()
{
  _canvas->pushState();
  _canvas->updateSheetRect();
}

void SelectGen::onScale(int x, int y)
{
  QPointF p(x, y);
  qreal rx = _select_rect->x();
  qreal ry = _select_rect->y();
  qreal rw = _select_rect->width();
  qreal rh = _select_rect->height();
  qreal dw = (p.x() - _start.x()) * (_mx2 - _mx1);
  qreal dh = (p.y() - _start.y()) * (_my2 - _my1);
  if (rw + dw < 20)
    dw = 20 - rw;
  if (rh + dh < 20)
    dh = 20 - rh;
  qreal dx = -dw * _mx1;
  qreal dy = -dh * _my1;
  for (Shape *item : _selected)
  {
    qreal ix = item->x();
    qreal iy = item->y();
    qreal iw = item->width();
    qreal ih = item->height();
    item->setX(ix + dw * (ix - rx) / rw + dx);
    item->setY(iy + dh * (iy - ry) / rh + dy);
    item->setWidth(iw + dw * iw / rw);
    item->setHeight(ih + dh * ih / rh);
  }
  updateRoundRect();
}

void SelectGen::onSheetPointChanged()
{
  if (!_selected.empty())
  {
    updateRoundRect();
  }
}

void SelectGen::onDel()
{
  if (_selected.empty()) return;
  for (Shape* shape : _selected)
  {
    delete shape;
  }
  _selected.clear();
  _select_rect->setVisible(false);
  _canvas_obj->paintObj()->setSelected(false);
  _canvas->pushState();
}

void SelectGen::onDuplicate()
{
  if (_selected.empty()) return;
  QByteArray data;
  QXmlStreamWriter writer(&data);
  writer.writeStartElement("dup");
  for (Shape *shape : _selected)
  {
    shape->serialize(&writer, _canvas);
  }
  writer.writeEndElement();
  QXmlStreamReader reader(data);
  reader.readNextStartElement();
  _selected.clear();
  _canvas_obj->deserializeShapes(&reader, &_selected);
  for (Shape *shape : _selected)
  {
    shape->setPosition(QPointF(shape->x() + 20, shape->y() + 20));
  }
  updateRoundRect();
  _canvas->pushState();
}

void SelectGen::updateRoundRect()
{
  Shape *item = _selected[0];
  qreal x1 = item->x();
  qreal y1 = item->y();
  qreal x2 = item->x() + item->width();
  qreal y2 = item->y() + item->height();
  int count = _selected.size();
  for (int i = 1; i < count; ++i)
  {
    item = _selected[i];
    x1 = qMin(x1, item->x());
    y1 = qMin(y1, item->y());
    x2 = qMax(x2, item->x() + item->width());
    y2 = qMax(y2, item->y() + item->height());
  }
  _select_rect->setPosition(QPointF(x1, y1));
  _select_rect->setSize(QSizeF(x2 - x1, y2 - y1));
}

QPointF SelectGen::getRectPoint(const QPointF &p)
{
  return QPointF((p.x() - _select_rect->x()) / _select_rect->width(),
                 (p.y() - _select_rect->y()) / _select_rect->height());
}
