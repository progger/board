/*
 * Copyright (C) 2012 Kulabuhov Michael, Kemerovo, Russia.
 *
 * See the LICENSE file for terms of use.
 */

#include <QFileDialog>
#include "paint.h"

Paint::Paint(QObject *parent) :
  QObject(parent),
  _mode("pen"),
  _thickness(3),
  _color("#000000"),
  _font_size(24),
  _selected(false),
  _can_undo(false),
  _can_redo(false),
  _image_data(),
  _image_size()
{
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
  QFileInfo file_info(file_name);
  QString ext = file_info.suffix();

  QString mime_type;
  if (ext == "png" || ext == "jpeg" || ext == "tiff" ||
      ext == "gif" || ext == "svg") {
    mime_type = ext;
  }
  else if (ext == "jpg") {
    mime_type = "jpg";
  }
  else if (ext == "tif") {
    mime_type = "tiff";
  }
  else {
    //TODO: error
    return;
  }

  QFile file(file_name);
  if (!file.open(QIODevice::ReadOnly)) {
    //TODO: error
    return;
  }
  QByteArray data = file.readAll();
  _image_data = "data:image/" + mime_type + ";base64," + data.toBase64();
  QImage image = QImage::fromData(data);
  _image_size = image.size();
  setMode("image");
}
