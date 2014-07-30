/*
 * Copyright (C) 2014 Michael Kulabuhov, Kemerovo, Russia.
 *
 * See the LICENSE file for terms of use.
 */

#ifndef PANEL_H
#define PANEL_H

#include "panelaction.h"

class Panel : public QQuickItem
{
  Q_OBJECT
  Q_PROPERTY(QColor color READ color WRITE setColor NOTIFY colorChanged)
  Q_PROPERTY(QQmlListProperty<PanelAction> actions READ actionsProperty NOTIFY actionsChanged)
public:
  explicit Panel(QQuickItem *parent = 0);
  QColor color() const { return _color; }
  QList<PanelAction*> actions() const { return _actions; }
  QQmlListProperty<PanelAction> actionsProperty();
signals:
  void colorChanged();
  void actionsChanged();
public slots:
  void setColor(QColor color);
  void addAction(PanelAction *action);
  void removeAction(PanelAction *action);
private:
  QColor _color;
  QList<PanelAction*> _actions;
};

#endif // PANEL_H
