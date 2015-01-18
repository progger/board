/*
 * Copyright (C) 2014 Michael Kulabuhov, Kemerovo, Russia.
 *
 * See the LICENSE file for terms of use.
 */

#ifndef PANEL_H
#define PANEL_H

#include <QQuickItem>
#include "tool.h"

class Panel : public QQuickItem
{
  Q_OBJECT
  Q_PROPERTY(QColor color READ color WRITE setColor NOTIFY colorChanged)
  Q_PROPERTY(QQmlListProperty<Tool> tools READ toolsProperty NOTIFY toolsChanged)
public:
  explicit Panel(QQuickItem *parent = 0);
  QColor color() const { return _color; }
  QList<Tool*> tools() const { return _tools; }
  QQmlListProperty<Tool> toolsProperty();
signals:
  void colorChanged();
  void toolsChanged();
public slots:
  void setColor(QColor color);
  void addTool(Tool *tool);
  void removeTool(Tool *tool);
private:
  QColor _color;
  QList<Tool*> _tools;
};

#endif // PANEL_H
