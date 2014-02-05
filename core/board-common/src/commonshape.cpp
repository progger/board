/*
 * Copyright (C) 2013 Michael Kulabuhov, Kemerovo, Russia.
 *
 * See the LICENSE file for terms of use.
 */

#include <QSGFlatColorMaterial>
#include "global.h"
#include "commonshape.h"

static QColor g_transparent_color = QColor(Qt::transparent);

CommonShape::CommonShape(QQuickItem *parent, float thickness, QColor color, QColor bgcolor) :
  Shape(parent, thickness, color, bgcolor),
  _main_node(nullptr),
  _background_node(nullptr),
  _clips()
{
  _clips.push_back(QRectF());
  connect(this, SIGNAL(innerSizeChanged()), SLOT(onInnerRectChanged()));
  connect(this, SIGNAL(thicknessChanged()), SLOT(onInnerRectChanged()));
}

void CommonShape::erase(const QRectF &beg, const QRectF &end)
{
  qreal sx = scalex();
  qreal sy = scaley();
  QRectF rect((beg.x() - x()) / sx, (beg.y() - y()) / sy, beg.width() / sx, beg.height() / sy);
  int steps = qMax(qAbs(end.x() - beg.x()), qAbs(end.y() - beg.y())) + 0.1;
  qreal dx = (end.x() - beg.x()) / steps / sx;
  qreal dy = (end.y() - beg.y()) / steps / sy;
  bool need_update = false;
  for (int i = 0; i < steps; ++i)
  {
    need_update = eraseRect(rect) || need_update;
    rect.setX(rect.x() + dx);
    rect.setY(rect.y() + dy);
  }
  if (need_update)
  {
    QByteArray data;
    QDataStream stream(&data, QIODevice::WriteOnly);
    for (const QRectF &clip : _clips)
    {
      stream << clip.x() << clip.y() << clip.width() << clip.height();
    }
    _clips_hash = g_core->brdStore()->addObject(data);
    update();
  }
}

QSGNode *CommonShape::updatePaintNode(QSGNode *node, QQuickItem::UpdatePaintNodeData *)
{
  QSGGeometry *g;
  if (!node)
  {
    QSGClipNode *clip_node = new QSGClipNode();
    g = new QSGGeometry(QSGGeometry::defaultAttributes_Point2D(), 6);
    g->setDrawingMode(GL_TRIANGLES);
    clip_node->setGeometry(g);
    clip_node->setFlag(QSGNode::OwnsGeometry);
    clip_node->setIsRectangular(false);
    node = clip_node;
  }
  updateClipNode(static_cast<QSGClipNode*>(node));

  if (hasMainNode())
  {
    if (color() == g_transparent_color)
    {
      if (_main_node)
      {
        node->removeChildNode(_main_node);
        delete _main_node;
        _main_node = nullptr;
      }
    }
    else
    {
      if (!_main_node)
      {
        QSGFlatColorMaterial *m = new QSGFlatColorMaterial;
        m->setColor(color());
        _main_node = new QSGGeometryNode();
        _main_node->setMaterial(m);
        _main_node->setFlag(QSGNode::OwnsMaterial);
        updateMainNode(_main_node);
        if (_background_node)
        {
          node->insertChildNodeAfter(_main_node, _background_node);
        }
        else
        {
          node->appendChildNode(_main_node);
        }
      }
      else
      {
        QSGFlatColorMaterial *m = static_cast<QSGFlatColorMaterial*>(_main_node->material());
        m->setColor(color());
        updateMainNode(_main_node);
      }
      _main_node->markDirty(QSGNode::DirtyGeometry | QSGNode::DirtyMaterial);
    }
  }

  if (hasBackgroundNode())
  {
    if (bgcolor() == g_transparent_color)
    {
      if (_background_node)
      {
        node->removeChildNode(_background_node);
        delete _background_node;
        _background_node = nullptr;
      }
    }
    else
    {
      if (!_background_node)
      {
        QSGFlatColorMaterial *m = new QSGFlatColorMaterial;
        m->setColor(bgcolor());
        _background_node = new QSGGeometryNode();
        _background_node->setMaterial(m);
        _background_node->setFlag(QSGNode::OwnsMaterial);
        updateBackgroundNode(_background_node);
        if (_main_node)
        {
          node->insertChildNodeBefore(_background_node, _main_node);
        }
        else
        {
          node->appendChildNode(_background_node);
        }
      }
      else
      {
        QSGFlatColorMaterial *m = static_cast<QSGFlatColorMaterial*>(_background_node->material());
        m->setColor(bgcolor());
        updateBackgroundNode(_background_node);
      }
      _background_node->markDirty(QSGNode::DirtyGeometry | QSGNode::DirtyMaterial);
    }
  }

  return node;
}

QRectF CommonShape::getFullInnerRect() const
{
  qreal t = thickness();
  QSizeF size = innerSize();
  return QRectF(-t / 2, -t / 2, size.width() + t, size.height() + t);
}

void CommonShape::innerSerialize(QXmlStreamWriter *writer, ISheetCanvas *, std::set<QString> *brd_objects) const
{
  writer->writeAttribute("clips_hash", _clips_hash);
  if (brd_objects) brd_objects->insert(_clips_hash);
}

void CommonShape::innerDeserialize(QXmlStreamReader *reader, ISheetCanvas *)
{
  _clips_hash = reader->attributes().value("clips_hash").toString();
  if (_clips_hash.isEmpty()) return;
  _clips.clear();
  QByteArray data = g_core->brdStore()->getObject(_clips_hash);
  QDataStream stream(data);
  while (!stream.atEnd())
  {
    qreal x, y, w, h;
    stream >> x >> y >> w >> h;
    _clips.push_back(QRectF(x, y, w, h));
  }
}

void CommonShape::onInnerRectChanged()
{
  if (_clips.size() == 1)
  {
    _clips.front() = getFullInnerRect();
  }
}

bool CommonShape::eraseRect(const QRectF &rect)
{
  bool need_update = false;
  auto it = _clips.begin();
  while (it != _clips.end())
  {
    QRectF &clip = *it;
    QRectF intersected = clip.intersected(rect);
    if (!intersected.width() || !intersected.height())
    {
      ++it;
      continue;
    }
    if (clip.x() < intersected.x())
    {
      _clips.push_front(QRectF(clip.x(), clip.y(),
                               intersected.x() - clip.x(), clip.height()));
    }
    if (clip.right() > intersected.right())
    {
      _clips.push_front(QRectF(intersected.right(), clip.y(),
                               clip.right() - intersected.right(), clip.height()));
    }
    if (clip.y() < intersected.y())
    {
      _clips.push_front(QRectF(intersected.x(), clip.y(),
                               intersected.width(), intersected.y() - clip.y()));
    }
    if (clip.bottom() > intersected.bottom())
    {
      _clips.push_front(QRectF(intersected.x(), intersected.bottom(),
                               intersected.width(), clip.bottom() - intersected.bottom()));
    }
    it = _clips.erase(it);
    need_update = true;
  }
  return need_update;
}

void CommonShape::updateClipNode(QSGClipNode *node)
{
  int vertext_count = _clips.size() * 6;
  auto g = node->geometry();
  if (g->vertexCount() != vertext_count)
  {
    g->allocate(vertext_count);
  }
  auto p = g->vertexDataAsPoint2D();
  qreal sx = scalex();
  qreal sy = scaley();
  int i = 0;
  for (QRectF &r : _clips)
  {
    QRectF rect(r.x() * sx, r.y() * sy, r.width() * sx, r.height() * sy);
    p[i++].set(rect.x(), rect.y());
    p[i++].set(rect.right(), rect.y());
    p[i++].set(rect.x(), rect.bottom());
    p[i++].set(rect.right(), rect.bottom());
    p[i++].set(rect.x(), rect.bottom());
    p[i++].set(rect.right(), rect.y());
  }
}
