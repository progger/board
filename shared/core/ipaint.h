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
#include <QSharedPointer>
#include "shapegen.h"
#include "isheetcanvas.h"

typedef QSharedPointer<ShapeGen>(*ShapeGenFunc)(ISheetCanvas *);
typedef Shape *(*ShapeFunc)();

class IPaint {
public:
  virtual ~IPaint() {}
  virtual Shape *createShape(const QString &name, ISheetCanvas *canvas) = 0;
  virtual QString mode() = 0;
  virtual float thickness() = 0;
  virtual QColor color() = 0;
  virtual QColor bgcolor() = 0;
  virtual int fontSize() = 0;
  virtual float eraserSize() = 0;
public slots:
  virtual void RegisterShapeGen(const QString &name, ShapeGenFunc func) = 0;
  virtual void RegisterShape(const QString &name, ShapeFunc func) = 0;
  virtual void RegisterCursor(const QString &name, const QCursor &cursor) = 0;
  virtual void setMode(const QString &mode) = 0;
  virtual void setThickness(float thickness) = 0;
  virtual void setColor(const QColor &color) = 0;
  virtual void setBgcolor(const QColor &bgcolor) = 0;
  virtual void setFontSize(int font_size) = 0;
  virtual void setEraserSize(float eraser_size) = 0;
signals:
  virtual void modeChanged() = 0;
  virtual void thicknessChanged() = 0;
  virtual void colorChanged() = 0;
  virtual void bgcolorChanged() = 0;
  virtual void fontSizeChanged() = 0;
  virtual void eraserSizeChanged() = 0;
};

Q_DECLARE_INTERFACE(IPaint, "board.core.IPaint")

#endif // IPAINT_H
