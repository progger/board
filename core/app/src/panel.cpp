/*
 * Copyright (C) 2014 Michael Kulabuhov, Kemerovo, Russia.
 *
 * See the LICENSE file for terms of use.
 */

#include "panel.h"

Panel::Panel(QQuickItem *parent) :
  QQuickItem(parent),
  _color(),
  _actions()
{
}

QQmlListProperty<PanelAction> Panel::actionsProperty()
{
  return QQmlListProperty<PanelAction>(this, nullptr,

    [](QQmlListProperty<PanelAction> *list) -> int
    {
      Panel *panel = qobject_cast<Panel*>(list->object);
      Q_ASSERT(panel);
      return panel->actions()->size();
    },

    [](QQmlListProperty<PanelAction> *list, int index) -> PanelAction*
    {
      Panel *panel = qobject_cast<Panel*>(list->object);
      Q_ASSERT(panel);
      return panel->actions()->at(index);
    });
}

void Panel::setColor(QColor color)
{
  _color = color;
  emit colorChanged();
}

void Panel::addAction(PanelAction *action)
{
  _actions.push_back(action);
  emit actionsChanged();
}

void Panel::removeAction(PanelAction *action)
{
  auto it = std::find(_actions.begin(), _actions.end(), action);
  if (it != _actions.end())
  {
    (*it)->deleteLater();
    _actions.erase(it);
  }
  emit actionsChanged();
}
