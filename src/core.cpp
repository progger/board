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
  font_size_(24)
{
}

QColor Core::selectColor(QColor color)
{
  return QColorDialog::getColor(color, view_);
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
  dialog.setFilter("*.svg");
  dialog.setDefaultSuffix("svg");
  if (dialog.exec())
  {
    QString file_name = dialog.selectedFiles().first();
    QByteArray data;
    data.append(XML_HEAD);
    data.append(DOCTYPE_SVG);
    data.append(content);
    QFile file(file_name);
    file.open(QIODevice::WriteOnly);
    file.write(data);
    file.close();
  }
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
