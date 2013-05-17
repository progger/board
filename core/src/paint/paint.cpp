/*
 * Copyright (C) 2012 Kulabuhov Michael, Kemerovo, Russia.
 *
 * See the LICENSE file for terms of use.
 */

#include <QFileDialog>
#include <QImage>
#include "../core.h"
#include "../brd/brdstore.h"
#include "paint.h"

using namespace std;

Paint::Paint(Core *parent) :
  QObject(parent),
  _mode("pen"),
  _thickness(3),
  _color("#000000"),
  _font_size(24),
  _selected(false),
  _can_undo(false),
  _can_redo(false),
  _image_source()
{
}

Core *Paint::core() const
{
  return static_cast<Core*>(parent());
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
  _image_source = obj->urlString();
  core()->brdStore()->setObject(obj);

  setMode("image");
}
