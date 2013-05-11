/*
 * Copyright (C) 2012 Kulabuhov Michael, Kemerovo, Russia.
 *
 * See the LICENSE file for terms of use.
 */

#include <QImage>
#include "paint.h"

using namespace Qt;

Paint::Paint(QObject *parent) :
  QObject(parent),
  _mode("pen"),
  _thickness(3),
  _color("#000000"),
  _font_size(24),
  _selected(false),
  _can_undo(false),
  _can_redo(false)
{
}

void Paint::selectImage()
{
  //TODO
  /*
  image_width_ = 0;
  image_height_ = 0;
  image_content_.clear();
  QFileDialog dialog(view_);
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

  QImage image(file_name);
  QFile file(file_name);
  if (!file.open(QIODevice::ReadOnly)) {
    showFileError(file);
    return;
  }
  QByteArray data = file.readAll();
  image_width_ = image.width();
  image_height_ = image.height();
  image_content_ = "data:image/" + mime_type + ";base64," + data.toBase64();
  */
}

void Paint::showFileError(const QFile &file)
{
  Q_UNUSED(file);
  //TODO
  //QMessageBox::critical(view_, ERROR_CAPTION, file.errorString());
}

void Paint::setMode(const QString &mode)
{
  _mode = mode;
  emit updateMode();
}

void Paint::setThickness(float thickness)
{
  _thickness = thickness;
  emit updateThickness();
}

void Paint::setColor(const QColor &color)
{
  _color = color;
  emit updateColor();
}

void Paint::setFontSize(int font_size)
{
  _font_size = font_size;
  emit updateFontSize();
}

void Paint::setSelected(bool selected)
{
  _selected = selected;
  emit updateSelected();
}

void Paint::setCanUndo(bool can_undo)
{
  _can_undo = can_undo;
  updateCanUndo();
}

void Paint::setCanRedo(bool can_redo)
{
  _can_redo = can_redo;
  updateCanRedo();
}
