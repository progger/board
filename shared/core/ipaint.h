/*
 * Copyright (C) 2012 Michael Kulabuhov, Kemerovo, Russia.
 *
 * See the LICENSE file for terms of use.
 */

#ifndef IPAINT_H
#define IPAINT_H

#include <QString>
#include <QColor>
#include <QCursor>
#include <memory>
#include "shapegen.h"
#include "isheetcanvas.h"

typedef std::shared_ptr<ShapeGen>(*ShapeGenFunc)(ISheetCanvas *);
typedef Shape *(*ShapeFunc)();

class IPaint {
public:
  virtual ~IPaint() {}
  virtual void RegisterShapeGen(const QString &name, ShapeGenFunc func) = 0;
  virtual void RegisterShape(const QString &name, ShapeFunc func) = 0;
  virtual void RegisterCursor(const QString &name, const QCursor &cursor) = 0;
  virtual QString mode() = 0;
  virtual void setMode(const QString &mode) = 0;
  virtual float thickness() = 0;
  virtual void setThickness(float thickness) = 0;
  virtual QColor color() = 0;
  virtual void setColor(const QColor &color) = 0;
  virtual QColor bgcolor() = 0;
  virtual void setBgcolor(const QColor &bgcolor) = 0;
  virtual int fontSize() = 0;
  virtual void setFontSize(int font_size) = 0;
  virtual float eraserSize() = 0;
  virtual void setEraserSize(float eraser_size) = 0;
};

Q_DECLARE_INTERFACE(IPaint, "board.core.IPaint")

#endif // IPAINT_H
