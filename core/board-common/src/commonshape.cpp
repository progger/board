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
  Shape(parent, thickness, std::move(color), std::move(bgcolor)),
  _main_node(nullptr),
  _background_node(nullptr),
  _clips()
{
  _clips.emplace_back();
  connect(this, SIGNAL(innerSizeChanged()), SLOT(onInnerRectChanged()));
  connect(this, SIGNAL(thicknessChanged()), SLOT(onInnerRectChanged()));
}

bool CommonShape::erase(const QRectF &beg, const QRectF &end)
{
  auto sx = scalex();
  auto sy = scaley();
  QRectF rect((beg.x() - x()) / sx, (beg.y() - y()) / sy, beg.width() / sx, beg.height() / sy);
  auto steps = static_cast<int>(std::max(std::abs(end.x() - beg.x()), std::abs(end.y() - beg.y())) * canvas()->zoom() + 0.1);
  steps = std::max(steps, 1);
  auto dx = (end.x() - beg.x()) / steps / sx;
  auto dy = (end.y() - beg.y()) / steps / sy;
  bool need_update = false;
  for (int i = 0; i <= steps; ++i)
  {
    need_update = eraseRect(rect) || need_update;
    rect.translate(dx, dy);
  }
  if (need_update)
  {
    update();
  }
  return need_update;
}

void CommonShape::updateClipHash()
{
  QByteArray data;
  QDataStream stream(&data, QIODevice::WriteOnly);
  for (const QRectF &clip : _clips)
  {
    stream << clip.x() << clip.y() << clip.width() << clip.height();
  }
  _clips_hash = g_core->brdStore()->addObject(data);
}

QSGNode *CommonShape::updatePaintNode(QSGNode *node, QQuickItem::UpdatePaintNodeData *)
{
  QSGGeometry *g;
  if (!node)
  {
    auto *clip_node = new QSGClipNode();
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
        auto *m = new QSGFlatColorMaterial;
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
        auto *m = static_cast<QSGFlatColorMaterial*>(_main_node->material());
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
        auto *m = new QSGFlatColorMaterial;
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
        auto *m = static_cast<QSGFlatColorMaterial*>(_background_node->material());
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
  return {-t / 2, -t / 2, size.width() + t, size.height() + t};
}

void CommonShape::innerSerialize(QXmlStreamWriter *writer, QSet<QString> *brd_objects) const
{
  Shape::innerSerialize(writer, brd_objects);
  writer->writeAttribute("common_shape_version", QString::number(1));
  if (!_clips_hash.isEmpty())
  {
    writer->writeAttribute("clips_hash", _clips_hash);
  }
  if (brd_objects) brd_objects->insert(_clips_hash);
}

void CommonShape::innerDeserialize(QXmlStreamReader *reader)
{
  Shape::innerDeserialize(reader);
  _clips_hash = reader->attributes().value("clips_hash").toString();
  if (_clips_hash.isEmpty()) return;
  _clips.clear();
  QByteArray data = g_core->brdStore()->getObject(_clips_hash);
  QDataStream stream(data);
  while (!stream.atEnd())
  {
    qreal x, y, w, h;
    stream >> x >> y >> w >> h;
    _clips.emplace_back(x, y, w, h);
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
    if (intersected.width() == 0 || intersected.height() == 0)
    {
      ++it;
      continue;
    }
    if (clip.x() < intersected.x())
    {
      _clips.emplace_front(clip.x(), clip.y(), intersected.x() - clip.x(), clip.height());
    }
    if (clip.right() > intersected.right())
    {
      _clips.emplace_front(intersected.right(), clip.y(), clip.right() - intersected.right(), clip.height());
    }
    if (clip.y() < intersected.y())
    {
      _clips.emplace_front(intersected.x(), clip.y(), intersected.width(), intersected.y() - clip.y());
    }
    if (clip.bottom() > intersected.bottom())
    {
      _clips.emplace_front(intersected.x(), intersected.bottom(), intersected.width(), clip.bottom() - intersected.bottom());
    }
    it = _clips.erase(it);
    need_update = true;
  }
  return need_update;
}

void CommonShape::updateClipNode(QSGClipNode *node)
{
  auto vertext_count = static_cast<int>(_clips.size()) * 6;
  auto *g = node->geometry();
  if (g->vertexCount() != vertext_count)
  {
    g->allocate(vertext_count);
  }
  auto *p = g->vertexDataAsPoint2D();
  auto sx = scalex();
  auto sy = scaley();
  int i = 0;
  for (QRectF &r : _clips)
  {
    QRectF rect(r.x() * sx, r.y() * sy, r.width() * sx, r.height() * sy);
    p[i++].set(static_cast<float>(rect.x()), static_cast<float>(rect.y()));
    p[i++].set(static_cast<float>(rect.right()), static_cast<float>(rect.y()));
    p[i++].set(static_cast<float>(rect.x()), static_cast<float>(rect.bottom()));
    p[i++].set(static_cast<float>(rect.right()), static_cast<float>(rect.bottom()));
    p[i++].set(static_cast<float>(rect.x()), static_cast<float>(rect.bottom()));
    p[i++].set(static_cast<float>(rect.right()), static_cast<float>(rect.y()));
  }
}
