/*
 * Copyright (C) 2012 Michael Kulabuhov, Kemerovo, Russia.
 *
 * See the LICENSE file for terms of use.
 */

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
#include "erasergen.h"
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
  _bgcolor(Qt::transparent),
  _font_size(42),
  _eraser_size(24),
  _selected(false),
  _can_undo(false),
  _can_redo(false),
  _image_size(),
  _image_hash(),
  _video_source(),
  _map_shape_gen(),
  _map_shape(),
  _map_cursor()
{
  RegisterShapeGen("select",    [](ISheetCanvas *canvas) -> shared_ptr<ShapeGen> { return make_shared<SelectGen>(canvas); });
  RegisterShapeGen("eraser",    [](ISheetCanvas *canvas) -> shared_ptr<ShapeGen> { return make_shared<EraserGen>(canvas); });
  RegisterShapeGen("pen",       [](ISheetCanvas *canvas) -> shared_ptr<ShapeGen> { return make_shared<PenGen>(canvas); });
  RegisterShapeGen("magic_pen", [](ISheetCanvas *canvas) -> shared_ptr<ShapeGen> { return make_shared<MagicPenGen>(canvas); });
  RegisterShapeGen("line",      [](ISheetCanvas *canvas) -> shared_ptr<ShapeGen> { return make_shared<LineGen>(canvas); });
  RegisterShapeGen("rectangle", [](ISheetCanvas *canvas) -> shared_ptr<ShapeGen> { return make_shared<RectangleGen>(canvas); });
  RegisterShapeGen("circle",    [](ISheetCanvas *canvas) -> shared_ptr<ShapeGen> { return make_shared<CircleGen>(canvas); });
  RegisterShapeGen("ellipse",   [](ISheetCanvas *canvas) -> shared_ptr<ShapeGen> { return make_shared<EllipseGen>(canvas); });
  RegisterShapeGen("text",      [](ISheetCanvas *canvas) -> shared_ptr<ShapeGen> { return make_shared<TextGen>(canvas); });
  RegisterShapeGen("move",      [](ISheetCanvas *canvas) -> shared_ptr<ShapeGen> { return make_shared<MoveGen>(canvas); });
  RegisterShapeGen("image",     [](ISheetCanvas *canvas) -> shared_ptr<ShapeGen> { return make_shared<ImageGen>(canvas); });
  RegisterShapeGen("video",     [](ISheetCanvas *canvas) -> shared_ptr<ShapeGen> { return make_shared<VideoGen>(canvas); });

  RegisterShape("pen",       []() -> Shape* { return new Pen(); });
  RegisterShape("line",      []() -> Shape* { return new Line(); });
  RegisterShape("rectangle", []() -> Shape* { return new class Rectangle(); });
  RegisterShape("ellipse",   []() -> Shape* { return new class Ellipse(); });
  RegisterShape("text",      []() -> Shape* { return static_cast<Shape*>(g_core->getComponent("qrc:/core/qml/TextWrapper.qml")->create()); });
  RegisterShape("image",     []() -> Shape* { return static_cast<Shape*>(g_core->getComponent("qrc:/core/qml/ImageWrapper.qml")->create()); });
  RegisterShape("video",     []() -> Shape* { return static_cast<Shape*>(g_core->getComponent("qrc:/core/qml/VideoPlayer.qml")->create()); });

  RegisterCursor("eraser", Qt::BlankCursor);
  RegisterCursor("pen", Qt::CrossCursor);
  RegisterCursor("magic_pen", Qt::CrossCursor);
  RegisterCursor("line", Qt::CrossCursor);
  RegisterCursor("rectangle", Qt::CrossCursor);
  RegisterCursor("circle", Qt::CrossCursor);
  RegisterCursor("ellipse", Qt::CrossCursor);
  RegisterCursor("text", Qt::IBeamCursor);
  RegisterCursor("move", Qt::OpenHandCursor);
  RegisterCursor("text", Qt::IBeamCursor);
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

QColor Paint::bgcolor()
{
  return _bgcolor;
}

int Paint::fontSize()
{
  return _font_size;
}

float Paint::eraserSize()
{
  return _eraser_size;
}

std::shared_ptr<ShapeGen> Paint::createShapeGen(ISheetCanvas *canvas) const
{
  auto it = _map_shape_gen.find(_mode);
  if (it == _map_shape_gen.cend()) return nullptr;
  return (*it).second(canvas);
}

Shape *Paint::createShape(const QString &name) const
{
  auto it = _map_shape.find(name);
  if (it == _map_shape.cend()) return nullptr;
  return (*it).second();
}

QCursor Paint::getCursor() const
{
  auto it = _map_cursor.find(_mode);
  if (it == _map_cursor.cend()) return Qt::ArrowCursor;
  return (*it).second;
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

void Paint::setBgcolor(const QColor &bgcolor)
{
  _bgcolor = bgcolor;
  emit bgcolorChanged();
}

void Paint::setFontSize(int font_size)
{
  _font_size = font_size;
  emit fontSizeChanged();
}

void Paint::setEraserSize(float eraser_size)
{
  _eraser_size = eraser_size;
  emit eraserSizeChanged();
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

void Paint::selectImage(const QString &file_name)
{
  QString hash = g_core->brdStore()->addFromFile(file_name);
  if (hash.isEmpty()) return;
  QImage image = QImage::fromData(g_core->brdStore()->getObject(hash));
  _image_size = image.size();
  _image_hash = hash;
  setMode("image");
}

void Paint::selectVideo(const QString &url)
{
  _video_source = url;
  setMode("video");
}


void Paint::RegisterShapeGen(const QString &name, ShapeGenFunc func)
{
  _map_shape_gen[name] = func;
}

void Paint::RegisterShape(const QString &name, ShapeFunc func)
{
  _map_shape[name] = func;
}

void Paint::RegisterCursor(const QString &name, const QCursor &cursor)
{
  _map_cursor[name] = cursor;
}
