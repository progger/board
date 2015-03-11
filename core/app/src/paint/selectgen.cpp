/*
 * Copyright (C) 2013 Michael Kulabuhov, Kemerovo, Russia.
 *
 * See the LICENSE file for terms of use.
 */

#include <algorithm>
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
  _container = _canvas_obj->container();
  _select_rect = _canvas_obj->selectRect();
  _select_rect->setProperty("selectGen", QVariant::fromValue<QObject*>(this));
  connect(_canvas_obj, SIGNAL(sheetPointChanged()), SLOT(onNeedUpdate()));
  connect(_canvas_obj->paintObj(), SIGNAL(scaleChanged()), SLOT(onNeedUpdate()));
  connect(_canvas_obj->paintObj(), SIGNAL(del()), SLOT(onDel()));
  connect(_canvas_obj->paintObj(), SIGNAL(duplicate()), SLOT(onDuplicate()));
  connect(_canvas_obj->paintObj(), SIGNAL(toFront()), SLOT(onToFront()));
  connect(_canvas_obj->paintObj(), SIGNAL(toBack()), SLOT(onToBack()));
  connect(_canvas_obj->paintObj(), SIGNAL(colorChanged()), SLOT(onColorChanged()));
  connect(_canvas_obj->paintObj(), SIGNAL(bgcolorChanged()), SLOT(onBgcolorChanged()));
}

SelectGen::~SelectGen()
{
  _select_rect->setVisible(false);
  _canvas_obj->paintObj()->setSelected(false);
}

void SelectGen::begin(const QPointF &p)
{
  QPointF sp = _canvas_obj->mapFromItem(_container, p);
  ShapeGen::begin(sp);
  _select_rect->setPosition(p);
  _select_rect->setSize(QSizeF(0, 0));
  _select_rect->setVisible(true);
  _select_rect->setProperty("bobberVisible", false);
  _selected.clear();
}

void SelectGen::end(const QPointF &p)
{
  move(p);
  QRectF select = _canvas_obj->mapRectToItem(_container, QRectF(_select_rect->x(), _select_rect->y(),_select_rect->width(), _select_rect->height()));
  bool click = select.width() < 8 && select.height() < 8;
  auto items = _canvas->container()->childItems();
  for (auto item : items)
  {
    Shape *shape = qobject_cast<Shape*>(item);
    if (!shape) continue;
    if (shape->checkIntersect(select))
    {
      _selected.append(shape);
    }
  }
  if (_selected.empty())
  {
    _select_rect->setVisible(false);
    _canvas_obj->paintObj()->setSelected(false);
  }
  else
  {
    if (click)
    {
      sortSelected();
      Shape *shape = _selected.back();
      _selected.clear();
      _selected.append(shape);
    }
    _select_rect->setProperty("bobberVisible", true);
    updateRoundRect();
    _canvas_obj->paintObj()->setSelected(true);
  }
}

void SelectGen::move(const QPointF &p)
{
  QPointF sp = _canvas_obj->mapFromItem(_container, p);
  qreal x1 = qMin(_start.x(), sp.x());
  qreal y1 = qMin(_start.y(), sp.y());
  qreal x2 = qMax(_start.x(), sp.x());
  qreal y2 = qMax(_start.y(), sp.y());
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
  QPointF dp = _canvas_obj->mapToItem(_container, p) - _canvas_obj->mapToItem(_container, _start);
  for (Shape *item : _selected)
  {
    item->setPosition(item->position() + dp);
  }
  _select_rect->setPosition(_select_rect->position() + p - _start);
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
  qreal rx = _select_rect->x();
  qreal ry = _select_rect->y();
  qreal rw = _select_rect->width();
  qreal rh = _select_rect->height();
  qreal dw = (x - _start.x()) * (_mx2 - _mx1);
  qreal dh = (y - _start.y()) * (_my2 - _my1);
  if (rw + dw < 20)
    dw = 20 - rw;
  if (rh + dh < 20)
    dh = 20 - rh;
  qreal dx = -dw * _mx1;
  qreal dy = -dh * _my1;
  for (Shape *item : _selected)
  {
    QRectF rect = _canvas_obj->mapRectFromItem(_container, QRectF(item->x(), item->y(), item->width(), item->height()));
    qreal ix = rect.x();
    qreal iy = rect.y();
    qreal iw = rect.width();
    qreal ih = rect.height();
    QRectF srect(ix + dw * (ix - rx) / rw + dx,
                 iy + dh * (iy - ry) / rh + dy,
                 iw + dw * iw / rw,
                 ih + dh * ih / rh);
    rect = _canvas_obj->mapRectToItem(_container, srect);
    item->setX(rect.x());
    item->setY(rect.y());
    item->setWidth(rect.width());
    item->setHeight(rect.height());
  }
  updateRoundRect();
}

void SelectGen::onNeedUpdate()
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
    shape->serialize(&writer);
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

void SelectGen::onToFront()
{
  if (_selected.empty()) return;
  sortSelected();
  int z = _canvas->getZMax();
  for (Shape *shape : _selected)
  {
    shape->setZ(++z);
  }
  _canvas->pushState();
}

void SelectGen::onToBack()
{
  if (_selected.empty()) return;
  sortSelected();
  int z = _canvas->getZMin();
  for (Shape *shape : _selected)
  {
    shape->setZ(--z);
  }
  _canvas->pushState();
}

void SelectGen::onColorChanged()
{
  if (_selected.empty()) return;
  for (Shape *shape : _selected)
  {
    shape->setColor(_canvas_obj->paintObj()->color());
  }
  _canvas->pushState();
}

void SelectGen::onBgcolorChanged()
{
  if (_selected.empty()) return;
  for (Shape *shape : _selected)
  {
    shape->setBgcolor(_canvas_obj->paintObj()->bgcolor());
  }
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
  QRectF rect = _canvas_obj->mapRectFromItem(_container, QRectF(x1, y1, x2 - x1, y2 - y1));
  _select_rect->setX(rect.x());
  _select_rect->setY(rect.y());
  _select_rect->setWidth(rect.width());
  _select_rect->setHeight(rect.height());
}

void SelectGen::sortSelected()
{
  std::sort(_selected.begin(), _selected.end(), [](Shape *s1, Shape *s2) { return s1->z() < s2->z(); });
}
