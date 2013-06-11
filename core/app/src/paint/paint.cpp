/*
 * Copyright (C) 2012 Kulabuhov Michael, Kemerovo, Russia.
 *
 * See the LICENSE file for terms of use.
 */

#include <QFileDialog>
#include <QImage>
#include "../core.h"
#include "../brd/brdstore.h"
#include "shapegen.h"
#include "selectgen.h"
#include "pengen.h"
#include "magicpengen.h"
#include "linegen.h"
#include "rectanglegen.h"
#include "circlegen.h"
#include "ellipsegen.h"
#include "textgen.h"
#include "movegen.h"
#include "imagegen.h"
#include "videogen.h"
#include "pen.h"
#include "line.h"
#include "rectangle.h"
#include "ellipse.h"
#include "textwrapper.h"
#include "imagewrapper.h"
#include "videoplayer.h"
#include "paint.h"

using namespace std;

Paint::Paint(Core *parent) :
  QObject(parent),
  _mode("pen"),
  _thickness(3),
  _color("#000000"),
  _font_size(42),
  _selected(false),
  _can_undo(false),
  _can_redo(false),
  _image_size(),
  _image_hash(),
  _video_source(),
  _map_shape_gen(),
  _map_shape()
{
  _comp_text_wrapper = parent->getComponent("qrc:/core/qml/TextWrapper.qml");
  _comp_image_wrapper = parent->getComponent("qrc:/core/qml/ImageWrapper.qml");
  _comp_video_player = parent->getComponent("qrc:/core/qml/VideoPlayer.qml");

  _map_shape_gen["select"] =    [](SheetCanvas *canvas) -> shared_ptr<ShapeGen> { return make_shared<SelectGen>(canvas); };
  _map_shape_gen["pen"] =       [](SheetCanvas *canvas) -> shared_ptr<ShapeGen> { return make_shared<PenGen>(canvas); };
  _map_shape_gen["magic_pen"] = [](SheetCanvas *canvas) -> shared_ptr<ShapeGen> { return make_shared<MagicPenGen>(canvas); };
  _map_shape_gen["line"] =      [](SheetCanvas *canvas) -> shared_ptr<ShapeGen> { return make_shared<LineGen>(canvas); };
  _map_shape_gen["rectangle"] = [](SheetCanvas *canvas) -> shared_ptr<ShapeGen> { return make_shared<RectangleGen>(canvas); };
  _map_shape_gen["circle"] =    [](SheetCanvas *canvas) -> shared_ptr<ShapeGen> { return make_shared<CircleGen>(canvas); };
  _map_shape_gen["ellipse"] =   [](SheetCanvas *canvas) -> shared_ptr<ShapeGen> { return make_shared<EllipseGen>(canvas); };
  _map_shape_gen["text"] =      [](SheetCanvas *canvas) -> shared_ptr<ShapeGen> { return make_shared<TextGen>(canvas); };
  _map_shape_gen["move"] =      [](SheetCanvas *canvas) -> shared_ptr<ShapeGen> { return make_shared<MoveGen>(canvas); };
  _map_shape_gen["image"] =     [](SheetCanvas *canvas) -> shared_ptr<ShapeGen> { return make_shared<ImageGen>(canvas); };
  _map_shape_gen["video"] =     [](SheetCanvas *canvas) -> shared_ptr<ShapeGen> { return make_shared<VideoGen>(canvas); };

  _map_shape["pen"] =       [](const Paint *paint) -> Shape* { return new Pen(paint->core()); };
  _map_shape["line"] =      [](const Paint *) -> Shape* { return new Line(); };
  _map_shape["rectangle"] = [](const Paint *) -> Shape* { return new class Rectangle(); };
  _map_shape["ellipse"] =   [](const Paint *) -> Shape* { return new class Ellipse(); };
  _map_shape["text"] =      [](const Paint *paint) -> Shape* { return static_cast<Shape*>(paint->compTextWrapper()->create()); };
  _map_shape["image"] =     [](const Paint *paint) -> Shape* { return static_cast<Shape*>(paint->compImageWrapper()->create()); };
  _map_shape["video"] =     [](const Paint *paint) -> Shape* { return static_cast<Shape*>(paint->compVideoPlayer()->create()); };
}

Core *Paint::core() const
{
  return static_cast<Core*>(parent());
}

std::shared_ptr<ShapeGen> Paint::createShapeGen(SheetCanvas *canvas) const
{
  auto it = _map_shape_gen.find(_mode);
  if (it == _map_shape_gen.cend()) return nullptr;
  return (*it).second(canvas);
}

Shape *Paint::createShape(const QString &name) const
{
  auto it = _map_shape.find(name);
  if (it == _map_shape.cend()) return nullptr;
  return (*it).second(this);
}

void Paint::setMode(const QString &mode)
{
  _mode = mode;
  emit modeChanged();
}

void Paint::setThickness(float thickness)
{
  _thickness = thickness;
  emit thicknessChanged();
}

void Paint::setColor(const QColor &color)
{
  _color = color;
  emit colorChanged();
}

void Paint::setFontSize(int font_size)
{
  _font_size = font_size;
  emit fontSizeChanged();
}

void Paint::setSelected(bool selected)
{
  _selected = selected;
  emit selectedChanged();
}

void Paint::setCanUndo(bool can_undo)
{
  _can_undo = can_undo;
  emit canUndoChanged();
}

void Paint::setCanRedo(bool can_redo)
{
  _can_redo = can_redo;
  emit canRedoChanged();
}

void Paint::selectImage()
{
  QFileDialog dialog;
  dialog.setAcceptMode(QFileDialog::AcceptOpen);
  dialog.setNameFilter("Image files (*.png *.jpg *.jpeg *.tif *.tiff *.gif *.svg)");
  if (!dialog.exec()) return;
  QString file_name = dialog.selectedFiles().first();

  auto obj = BrdStore::fromFile(file_name);
  if (!obj) return;
  QImage image = QImage::fromData(obj->data());
  _image_size = image.size();
  _image_hash = obj->hash();
  core()->brdStore()->setObject(obj);

  setMode("image");
}

void Paint::selectVideo()
{
  QFileDialog dialog;
  dialog.setAcceptMode(QFileDialog::AcceptOpen);
  //dialog.setNameFilter("Video files (*.avi)");  //TODO
  if (!dialog.exec()) return;
  QString file_name = dialog.selectedFiles().first();
  _video_source = "file:///" + file_name;
  setMode("video");
}
