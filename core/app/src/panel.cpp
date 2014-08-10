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

QQmlListProperty<PanelTool> Panel::toolsProperty()
{
  return QQmlListProperty<PanelTool>(this, nullptr,

    [](QQmlListProperty<PanelTool> *list) -> int
    {
      Panel *panel = qobject_cast<Panel*>(list->object);
      Q_ASSERT(panel);
      return panel->tools().size();
    },

    [](QQmlListProperty<PanelTool> *list, int index) -> PanelTool*
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

void Panel::addTool(PanelTool *tool)
{
  _tools.append(tool);
  emit toolsChanged();
}

void Panel::removeTool(PanelTool *tool)
{
  _tools.removeAll(tool);
  emit toolsChanged();
}
