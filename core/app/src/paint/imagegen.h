/*
 * Copyright (C) 2013 Michael Kulabuhov, Kemerovo, Russia.
 *
 * See the LICENSE file for terms of use.
 */

#ifndef IMAGEGEN_H
#define IMAGEGEN_H

#include <memory>
#include "shapegen.h"

class ImageGen : public ShapeGen
{
  Q_DISABLE_COPY_MOVE(ImageGen)
public:
  explicit ImageGen(ISheetCanvas *canvas);
  ~ImageGen() override = default;
  void begin(const QPointF &p) override;
  void end(const QPointF &p) override;
  void move(const QPointF &p) override;
private:
  QSize _image_size;
  QString _image_hash;
};

#endif // IMAGEGEN_H
