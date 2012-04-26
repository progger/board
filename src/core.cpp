/*
 * Copyright (C) 2012 Kulabuhov Michael, Kemerovo, Russia.
 *
 * See the LICENSE file for terms of use.
 */

#include <QApplication>
#include <QWidget>
#include <QKeyEvent>
#include <QColorDialog>
#include <QFileDialog>
#include <QMessageBox>
#include <QFileInfo>
#include <QImage>
#include "const.h"
#include "core.h"
#include "mainview.h"

using namespace Qt;

Core::Core(MainView *view) :
  QObject(view),
  view_(view),
  mode_("pen"),
  thickness_(3),
  color_("#000000"),
  keyboard_(false),
  font_size_(24),
  selected_(false),
  image_width_(0),
  image_height_(0),
  image_content_(""),
  can_undo_(false),
  can_redo_(false)
{
}

QColor Core::selectColor(QColor color)
{
  return QColorDialog::getColor(color, view_);
}

void Core::selectImage()
{
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
}

void Core::emulateKeyPress(int key, int modifiers, const QString &text) const
{
  KeyboardModifiers md = KeyboardModifiers(modifiers);
  QKeyEvent *event = new QKeyEvent(QEvent::KeyPress, key, md, text);
  QApplication::postEvent(QApplication::focusWidget(), event);
}

void Core::saveContent(const QString &content)
{
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
}

void Core::showFileError(const QFile &file)
{
  QMessageBox::critical(view_, ERROR_CAPTION, file.errorString());
}

void Core::setMode(const QString &mode)
{
  mode_ = mode;
  emit updateMode();
}

void Core::setThickness(float thickness)
{
  thickness_ = thickness;
  emit updateThickness();
}

void Core::setColor(const QString &color)
{
  color_ = color;
  emit updateColor();
}

void Core::setKeyboard(bool keyboard)
{
  keyboard_ = keyboard;
  emit updateKeyboard();
}

void Core::setFontSize(int font_size)
{
  font_size_ = font_size;
  emit updateFontSize();
}

void Core::setSelected(bool selected)
{
  selected_ = selected;
  emit updateSelected();
}

void Core::setImageContent(const QString &imageContent)
{
  image_content_ = imageContent;
  updateImageContent();
}

void Core::setCanUndo(bool can_undo)
{
  can_undo_ = can_undo;
  updateCanUndo();
}

void Core::setCanRedo(bool can_redo)
{
  can_redo_ = can_redo;
  updateCanRedo();
}

void Core::setImageWidth(int width)
{
  image_width_ = width;
  updateImageWidth();
}

void Core::setImageHeight(int height)
{
  image_height_ = height;
  updateImageHeight();
}
