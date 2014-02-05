#ifndef ERASERGEN_H
#define ERASERGEN_H

#include "shapegen.h"

class EraserGen : public ShapeGen
{
public:
  explicit EraserGen(ISheetCanvas *canvas);
  virtual void begin(const QPointF &p) override;
  virtual void end(const QPointF &p) override;
  virtual void move(const QPointF &p) override;
};

#endif // ERASERGEN_H
