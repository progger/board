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
  Q_PROPERTY(int buttonX READ buttonX WRITE setButtonX NOTIFY buttonXChanged)
  Q_PROPERTY(int buttonY READ buttonY WRITE setButtonY NOTIFY buttonYChanged)
  Q_PROPERTY(int buttonWidth READ buttonWidth WRITE setButtonWidth NOTIFY buttonWidthChanged)
  Q_PROPERTY(int buttonHeight READ buttonHeight WRITE setButtonHeight NOTIFY buttonHeightChanged)
public:
  explicit PanelTool(QQuickItem *parent = 0);
  QString name() const { return _name; }
  void setName(const QString &name);
  int buttonX() const { return _button_x; }
  int buttonY() const { return _button_y; }
  int buttonWidth() const { return _button_width; }
  int buttonHeight() const { return _button_height; }
signals:
  void buttonXChanged();
  void buttonYChanged();
  void buttonWidthChanged();
  void buttonHeightChanged();
public slots:
  void setButtonX(int x);
  void setButtonY(int y);
  void setButtonWidth(int width);
  void setButtonHeight(int height);
private:
  QString _name;
  int _button_x;
  int _button_y;
  int _button_width;
  int _button_height;
};

#endif // PANELTOOL_H
