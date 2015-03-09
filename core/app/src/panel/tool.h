/*
 * Copyright (C) 2014 Michael Kulabuhov, Kemerovo, Russia.
 *
 * See the LICENSE file for terms of use.
 */

#ifndef TOOL_H
#define TOOL_H

#include "toolinfo.h"

class Tool : public ToolInfo
{
  Q_OBJECT
  Q_PROPERTY(int x READ x WRITE setX NOTIFY xChanged)
  Q_PROPERTY(int y READ y WRITE setY NOTIFY yChanged)
public:
  Tool(ToolInfo *tool_info, QObject *parent = 0);
  int x() const { return _x; }
  int y() const { return _y; }
signals:
  void xChanged();
  void yChanged();
public slots:
  void setX(int x);
  void setY(int y);
private:
  int _x;
  int _y;
};

#endif // TOOL_H
