/*
 * Copyright (C) 2014 Michael Kulabuhov, Kemerovo, Russia.
 *
 * See the LICENSE file for terms of use.
 */

#include "panel.h"

Panel::Panel(QObject *parent) :
  QObject(parent),
  _x(0),
  _y(0),
  _width(0),
  _height(0),
  _color(),
  _tools()
{
}

QQmlListProperty<Tool> Panel::toolsProperty()
{
  auto count_func = [](QQmlListProperty<Tool> *list)
  {
    auto *panel = qobject_cast<Panel*>(list->object);
    Q_ASSERT(panel);
    return panel->tools().size();
  };
  auto at_func =  [](QQmlListProperty<Tool> *list, int index)
  {
    auto *panel = qobject_cast<Panel*>(list->object);
    Q_ASSERT(panel);
    return panel->tools().at(index);
  };
  return {this, nullptr, count_func, at_func};
}

void Panel::setX(int x)
{
  _x = x;
  emit xChanged();
}

void Panel::setY(int y)
{
  _y = y;
  emit yChanged();
}

void Panel::setColor(QColor color)
{
  _color = std::move(color);
  emit colorChanged();
}

void Panel::addTool(Tool *tool)
{
  _tools.append(tool);
  updateSize();
  emit toolsChanged();
}

void Panel::removeTool(Tool *tool)
{
  _tools.removeAll(tool);
  tool->deleteLater();
  updateSize();
  emit toolsChanged();
}

void Panel::updateSize()
{
  _width = 0;
  _height = 0;
  for (Tool *tool : _tools)
  {
    int w = tool->x() + tool->width();
    if (_width < w) _width = w;
    int h = tool->y() + tool->height();
    if (_height < h) _height = h;
  }
}
