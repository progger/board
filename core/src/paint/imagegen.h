/*
 * Copyright (C) 2013 Kulabuhov Michael, Kemerovo, Russia.
 *
 * See the LICENSE file for terms of use.
 */

#ifndef IMAGEGEN_H
#define IMAGEGEN_H

#include <memory>
#include "shapegen.h"

class ImageGen : public ShapeGen
{
public:
  explicit ImageGen(SheetCanvas *canvas);
  virtual void begin(const QPointF &p) override;
  virtual void end(const QPointF &p) override;
  virtual void move(const QPointF &p) override;
  static std::shared_ptr<ShapeGen> openFile(SheetCanvas *canvas);
private:
  QSize _image_size;
  QString _image_hash;
};

#endif // IMAGEGEN_H
