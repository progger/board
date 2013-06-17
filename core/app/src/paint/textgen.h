/*
 * Copyright (C) 2013 Michael Kulabuhov, Kemerovo, Russia.
 *
 * See the LICENSE file for terms of use.
 */

#ifndef TEXTGEN_H
#define TEXTGEN_H

#include "shapegen.h"

class TextGen : public QObject, public ShapeGen
{
  Q_OBJECT
public:
  explicit TextGen(ISheetCanvas *canvas);
  virtual ~TextGen() override;
  virtual void begin(const QPointF &);
  virtual void end(const QPointF &p);
  virtual void move(const QPointF &);
public slots:
  void endEdit();
private:
  QQuickItem *_text_input;
};

#endif // TEXTGEN_H
