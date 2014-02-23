#ifndef ERASERGEN_H
#define ERASERGEN_H

#include <set>
#include "commonshape.h"
#include "shapegen.h"

class EraserGen : public ShapeGen
{
public:
  explicit EraserGen(ISheetCanvas *canvas);
  virtual void begin(const QPointF &p) override;
  virtual void end(const QPointF &p) override;
  virtual void move(const QPointF &p) override;
private:
  std::set<CommonShape*> _shape_set;
};

#endif // ERASERGEN_H
