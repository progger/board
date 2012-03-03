/*
 * Copyright (C) 2011 Kulabuhov Michael, Kemerovo, Russia.
 *
 * See the LICENSE file for terms of use.
 */

#ifndef BOARDDRAW_H
#define BOARDDRAW_H

#include <QObject>

class BoardDraw : public QObject
{
  Q_OBJECT
public:
  explicit BoardDraw(QObject *parent = 0);
  bool getState() { return state_; }
  QString getMode() { return mode_; }
  QString getColor() { return color_; }
  Q_PROPERTY(bool state READ getState WRITE setState)
  Q_PROPERTY(QString mode READ getMode WRITE setMode)
  Q_PROPERTY(QString color READ getColor WRITE setColor)

signals:
  void modeChanged();

public slots:
  void setState(bool state) { state_ = state; }
  void setMode(const QString &mode);
  void setColor(const QString &color) { color_ = color; }

private:
  bool state_;
  QString mode_;
  QString color_;
};

#endif // BOARDDRAW_H
