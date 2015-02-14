/*
 * Copyright (C) 2014 Michael Kulabuhov, Kemerovo, Russia.
 *
 * See the LICENSE file for terms of use.
 */

#ifndef PANEL_H
#define PANEL_H

#include <QObject>
#include <QQmlListProperty>
#include <QColor>
#include "tool.h"

class Panel : public QObject
{
  Q_OBJECT
  Q_PROPERTY(int x READ x WRITE setX NOTIFY xChanged)
  Q_PROPERTY(int y READ y WRITE setY NOTIFY yChanged)
  Q_PROPERTY(int width READ width NOTIFY toolsChanged)
  Q_PROPERTY(int height READ height NOTIFY toolsChanged)
  Q_PROPERTY(QColor color READ color WRITE setColor NOTIFY colorChanged)
  Q_PROPERTY(QQmlListProperty<Tool> tools READ toolsProperty NOTIFY toolsChanged)
public:
  explicit Panel(QObject *parent = 0);
  int x() const { return _x; }
  int y() const { return _y; }
  int width() const { return _width; }
  int height() const { return _height; }
  QColor color() const { return _color; }
  QList<Tool*> tools() const { return _tools; }
  QQmlListProperty<Tool> toolsProperty();
signals:
  void xChanged();
  void yChanged();
  void colorChanged();
  void toolsChanged();
public slots:
  void setX(int x);
  void setY(int y);
  void setColor(QColor color);
  void addTool(Tool *tool);
  void removeTool(Tool *tool);
private:
  int _x;
  int _y;
  int _width;
  int _height;
  QColor _color;
  QList<Tool*> _tools;
  void updateSize();
};

#endif // PANEL_H
