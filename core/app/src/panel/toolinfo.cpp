/*
 * Copyright (C) 2014 Michael Kulabuhov, Kemerovo, Russia.
 *
 * See the LICENSE file for terms of use.
 */

#include "toolinfo.h"

ToolInfo::ToolInfo(const QString &name, const QString &section, QQmlComponent *component, int width, int height, QObject *parent) :
  QObject(parent),
  _name(name),
  _section(section),
  _component(component),
  _width(width),
  _height(height)
{
}

void ToolInfo::create(QQuickItem *parent) const
{
  auto *obj = component()->create();
  auto *item = qobject_cast<QQuickItem*>(obj);
  Q_ASSERT(item);
  item->setParent(parent);
  item->setParentItem(parent);
}
