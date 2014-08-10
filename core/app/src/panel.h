/*
 * Copyright (C) 2014 Michael Kulabuhov, Kemerovo, Russia.
 *
 * See the LICENSE file for terms of use.
 */

#ifndef PANEL_H
#define PANEL_H

#include "paneltool.h"

class Panel : public QQuickItem
{
  Q_OBJECT
  Q_PROPERTY(QColor color READ color WRITE setColor NOTIFY colorChanged)
  Q_PROPERTY(QQmlListProperty<PanelTool> tools READ toolsProperty NOTIFY toolsChanged)
public:
  explicit Panel(QQuickItem *parent = 0);
  QColor color() const { return _color; }
  QList<PanelTool*> tools() const { return _tools; }
  QQmlListProperty<PanelTool> toolsProperty();
signals:
  void colorChanged();
  void toolsChanged();
public slots:
  void setColor(QColor color);
  void addTool(PanelTool *tool);
  void removeTool(PanelTool *tool);
private:
  QColor _color;
  QList<PanelTool*> _tools;
};

#endif // PANEL_H
