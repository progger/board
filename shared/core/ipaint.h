/*
 * Copyright (C) 2012 Michael Kulabuhov, Kemerovo, Russia.
 *
 * See the LICENSE file for terms of use.
 */

#ifndef IPAINT_H
#define IPAINT_H

#include <QString>
#include <QColor>

class IPaint {
public:
  virtual ~IPaint() {}
  virtual QString mode() = 0;
  virtual float thickness() = 0;
  virtual QColor color() = 0;
  virtual int fontSize() = 0;
  virtual void setMode(const QString &mode) = 0;
  virtual void setThickness(float thickness) = 0;
  virtual void setColor(const QColor &color) = 0;
  virtual void setFontSize(int font_size) = 0;
};

Q_DECLARE_INTERFACE(IPaint, "board.core.IPaint/2.0")

#endif // IPAINT_H
