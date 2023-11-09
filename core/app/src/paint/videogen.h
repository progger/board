/*
 * Copyright (C) 2013 Michael Kulabuhov, Kemerovo, Russia.
 *
 * See the LICENSE file for terms of use.
 */

#ifndef VIDEOGEN_H
#define VIDEOGEN_H

#include "shapegen.h"

class VideoGen : public ShapeGen
{
  Q_DISABLE_COPY_MOVE(VideoGen)
public:
  explicit VideoGen(ISheetCanvas *canvas);
  ~VideoGen() override = default;
  void begin(const QPointF &p) override;
  void end(const QPointF &p) override;
  void move(const QPointF &p) override;
private:
  QString _video_source;
};

#endif // VIDEOGEN_H
