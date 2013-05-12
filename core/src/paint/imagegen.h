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
  explicit ImageGen(SheetCanvas *canvas, QSizeF image_size, QString image_data);
  virtual void begin(const QPointF &p) override;
  virtual void end(const QPointF &p) override;
  virtual void move(const QPointF &p) override;
  static std::shared_ptr<ShapeGen> openFile(SheetCanvas *canvas);
private:
  QSizeF _image_size;
  QString _image_data;
};

#endif // IMAGEGEN_H
