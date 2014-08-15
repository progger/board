/*
 * Copyright (C) 2014 Michael Kulabuhov, Kemerovo, Russia.
 *
 * See the LICENSE file for terms of use.
 */

#ifndef PANELTOOL_H
#define PANELTOOL_H

#include <QQuickItem>

class PanelTool : public QQuickItem
{
  Q_OBJECT
  Q_PROPERTY(int toolWidth READ toolWidth WRITE setToolWidth NOTIFY toolWidthChanged)
  Q_PROPERTY(int toolHeight READ toolHeight WRITE setToolHeight NOTIFY toolHeightChanged)
public:
  explicit PanelTool(QQuickItem *parent = 0);
  int toolWidth() const { return _tool_width; }
  int toolHeight() const { return _tool_height; }
signals:
  void toolWidthChanged();
  void toolHeightChanged();
public slots:
  void setToolWidth(int width);
  void setToolHeight(int height);
private:
  int _tool_width;
  int _tool_height;
};

#endif // PANELTOOL_H
