/*
 * Copyright (C) 2013 Kulabuhov Michael, Kemerovo, Russia.
 *
 * See the LICENSE file for terms of use.
 */

#ifndef VIDEOGEN_H
#define VIDEOGEN_H

#include "shapegen.h"

class VideoGen : public ShapeGen
{
public:
  explicit VideoGen(ISheetCanvas *canvas);
  virtual void begin(const QPointF &p) override;
  virtual void end(const QPointF &p) override;
  virtual void move(const QPointF &p) override;
private:
  QString _video_source;
};

#endif // VIDEOGEN_H
