/*
 * Copyright (C) 2014 Michael Kulabuhov, Kemerovo, Russia.
 *
 * See the LICENSE file for terms of use.
 */

#include "panel.h"

Panel::Panel(QQuickItem *parent) :
  QQuickItem(parent),
  _color(),
  _tools()
{
}

QQmlListProperty<Tool> Panel::toolsProperty()
{
  return QQmlListProperty<Tool>(this, nullptr,

    [](QQmlListProperty<Tool> *list) -> int
    {
      Panel *panel = qobject_cast<Panel*>(list->object);
      Q_ASSERT(panel);
      return panel->tools().size();
    },

    [](QQmlListProperty<Tool> *list, int index) -> Tool*
    {
      Panel *panel = qobject_cast<Panel*>(list->object);
      Q_ASSERT(panel);
      return panel->tools().at(index);
    });
}

void Panel::setColor(QColor color)
{
  _color = color;
  emit colorChanged();
}

void Panel::addTool(Tool *tool)
{
  _tools.append(tool);
  emit toolsChanged();
}

void Panel::removeTool(Tool *tool)
{
  _tools.removeAll(tool);
  tool->deleteLater();
  emit toolsChanged();
}
