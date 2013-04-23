/*
 * Copyright (C) 2012 Kulabuhov Michael, Kemerovo, Russia.
 *
 * See the LICENSE file for terms of use.
 */

#include <QImage>
#include "const.h"
#include "paint.h"

using namespace Qt;

Paint::Paint(QObject *parent) :
  QObject(parent),
  mode_("pen"),
  thickness_(3),
  color_("#000000"),
  font_size_(24),
  selected_(false),
  image_width_(0),
  image_height_(0),
  image_content_(""),
  can_undo_(false),
  can_redo_(false)
{
}

QColor Paint::selectColor(QColor color)
{
  //TODO
  //return QColorDialog::getColor(color);
  return QColor();
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

void Paint::saveContent(const QString &content)
{
  //TODO
  /*
  QFileDialog dialog(view_);
  dialog.setAcceptMode(QFileDialog::AcceptSave);
  dialog.setNameFilter("*.svg");
  dialog.setDefaultSuffix("svg");
  if (dialog.exec())
  {
    QString file_name = dialog.selectedFiles().first();
    QByteArray data;
    data.append(XML_HEAD);
    data.append(DOCTYPE_SVG);
    data.append(content);
    QFile file(file_name);
    if (!file.open(QIODevice::WriteOnly)) {
      showFileError(file);
      return;
    }
    if (!file.write(data)) {
      showFileError(file);
    }
    file.close();
  }
  */
}

void Paint::showFileError(const QFile &file)
{
  //TODO
  //QMessageBox::critical(view_, ERROR_CAPTION, file.errorString());
}

void Paint::setMode(const QString &mode)
{
  mode_ = mode;
  emit updateMode();
}

void Paint::setThickness(float thickness)
{
  thickness_ = thickness;
  emit updateThickness();
}

void Paint::setColor(const QColor &color)
{
  color_ = color;
  emit updateColor();
}

void Paint::setFontSize(int font_size)
{
  font_size_ = font_size;
  emit updateFontSize();
}

void Paint::setSelected(bool selected)
{
  selected_ = selected;
  emit updateSelected();
}

void Paint::setImageContent(const QString &imageContent)
{
  image_content_ = imageContent;
  updateImageContent();
}

void Paint::setCanUndo(bool can_undo)
{
  can_undo_ = can_undo;
  updateCanUndo();
}

void Paint::setCanRedo(bool can_redo)
{
  can_redo_ = can_redo;
  updateCanRedo();
}

void Paint::setImageWidth(int width)
{
  image_width_ = width;
  updateImageWidth();
}

void Paint::setImageHeight(int height)
{
  image_height_ = height;
  updateImageHeight();
}
