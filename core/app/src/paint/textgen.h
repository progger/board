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
  Q_DISABLE_COPY_MOVE(TextGen)
public:
  explicit TextGen(ISheetCanvas *canvas);
  ~TextGen() override;
  void begin(const QPointF &) override;
  void end(const QPointF &p) override;
  void move(const QPointF &) override;
public slots:
  void endEdit();
private:
  QQuickItem *_text_input;
};

#endif // TEXTGEN_H
