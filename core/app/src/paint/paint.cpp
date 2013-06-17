/*
 * Copyright (C) 2012 Michael Kulabuhov, Kemerovo, Russia.
 *
 * See the LICENSE file for terms of use.
 */

#include <QFileDialog>
#include <QImage>
#include "global.h"
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
  _map_shape_gen["select"] =    [](ISheetCanvas *canvas) -> shared_ptr<ShapeGen> { return make_shared<SelectGen>(canvas); };
  _map_shape_gen["pen"] =       [](ISheetCanvas *canvas) -> shared_ptr<ShapeGen> { return make_shared<PenGen>(canvas); };
  _map_shape_gen["magic_pen"] = [](ISheetCanvas *canvas) -> shared_ptr<ShapeGen> { return make_shared<MagicPenGen>(canvas); };
  _map_shape_gen["line"] =      [](ISheetCanvas *canvas) -> shared_ptr<ShapeGen> { return make_shared<LineGen>(canvas); };
  _map_shape_gen["rectangle"] = [](ISheetCanvas *canvas) -> shared_ptr<ShapeGen> { return make_shared<RectangleGen>(canvas); };
  _map_shape_gen["circle"] =    [](ISheetCanvas *canvas) -> shared_ptr<ShapeGen> { return make_shared<CircleGen>(canvas); };
  _map_shape_gen["ellipse"] =   [](ISheetCanvas *canvas) -> shared_ptr<ShapeGen> { return make_shared<EllipseGen>(canvas); };
  _map_shape_gen["text"] =      [](ISheetCanvas *canvas) -> shared_ptr<ShapeGen> { return make_shared<TextGen>(canvas); };
  _map_shape_gen["move"] =      [](ISheetCanvas *canvas) -> shared_ptr<ShapeGen> { return make_shared<MoveGen>(canvas); };
  _map_shape_gen["image"] =     [](ISheetCanvas *canvas) -> shared_ptr<ShapeGen> { return make_shared<ImageGen>(canvas); };
  _map_shape_gen["video"] =     [](ISheetCanvas *canvas) -> shared_ptr<ShapeGen> { return make_shared<VideoGen>(canvas); };

  _map_shape["pen"] =       []() -> Shape* { return new Pen(); };
  _map_shape["line"] =      []() -> Shape* { return new Line(); };
  _map_shape["rectangle"] = []() -> Shape* { return new class Rectangle(); };
  _map_shape["ellipse"] =   []() -> Shape* { return new class Ellipse(); };
  _map_shape["text"] =      []() -> Shape* { return static_cast<Shape*>(g_core->getComponent("qrc:/core/qml/TextWrapper.qml")->create()); };
  _map_shape["image"] =     []() -> Shape* { return static_cast<Shape*>(g_core->getComponent("qrc:/core/qml/ImageWrapper.qml")->create()); };
  _map_shape["video"] =     []() -> Shape* { return static_cast<Shape*>(g_core->getComponent("qrc:/core/qml/VideoPlayer.qml")->create()); };
}

QString Paint::mode()
{
  return _mode;
}

float Paint::thickness()
{
  return _thickness;
}

QColor Paint::color()
{
  return _color;
}

int Paint::fontSize()
{
  return _font_size;
}

std::shared_ptr<ShapeGen> Paint::createShapeGen(ISheetCanvas *canvas) const
{
  auto it = _map_shape_gen.find(_mode);
  if (it == _map_shape_gen.cend()) return nullptr;
  return (*it).second(canvas);
}

Shape *Paint::createShape(const QString &name)
{
  auto it = _map_shape.find(name);
  if (it == _map_shape.cend()) return nullptr;
  return (*it).second();
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

  QString hash = g_core->brdStore()->addFromFile(file_name);
  if (hash.isEmpty()) return;
  QImage image = QImage::fromData(g_core->brdStore()->getObject(hash));
  _image_size = image.size();
  _image_hash = hash;
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
