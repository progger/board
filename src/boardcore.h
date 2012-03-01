/*
 * Copyright (C) 2011 Kulabuhov Michail, Kemerovo, Russia.
 *
 * See the LICENSE file for terms of use.
 */

#ifndef BOARDCORE_H
#define BOARDCORE_H

#include <QObject>

class BoardCore : public QObject
{
  Q_OBJECT
public:
  explicit BoardCore(QObject *parent = 0);
  bool getState() { return state_; }
  QString getMode() { return mode_; }
  QString getColor() { return color_; }
  Q_PROPERTY(bool state READ getState WRITE setState)
  Q_PROPERTY(QString mode READ getMode WRITE setMode)
  Q_PROPERTY(QString color READ getColor WRITE setColor)

signals:
  void modeChanged();

public slots:
  void readyToWork();
  void setState(bool state) { state_ = state; }
  void setMode(const QString &mode);
  void setColor(const QString &color) { color_ = color; }

private:
  bool state_;
  QString mode_;
  QString color_;
};

#endif // BOARDCORE_H
