/*
 * Copyright (C) 2013 Michael Kulabuhov, Kemerovo, Russia.
 *
 * See the LICENSE file for terms of use.
 */

#include <QSGFlatColorMaterial>
#include "commonshape.h"

static QColor g_transparent_color = QColor(Qt::transparent);

CommonShape::CommonShape(QQuickItem *parent, float thickness, QColor color, QColor bgcolor) :
  Shape(parent, thickness, color, bgcolor),
  _main_node(nullptr),
  _background_node(nullptr)
{
}

QSGNode *CommonShape::updatePaintNode(QSGNode *node, QQuickItem::UpdatePaintNodeData *)
{
  if (!node)
  {
    node = new QSGNode();
  }
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
  return node;
}
