/*
 * Copyright (C) 2012 Kulabuhov Michael, Kemerovo, Russia.
 *
 * See the LICENSE file for terms of use.
 */

#include <QApplication>
#include <QWidget>
#include <QKeyEvent>
#include <QColorDialog>
#include "core.h"
#include "mainview.h"

using namespace Qt;

Core::Core(MainView *view) :
  QObject(view),
  view_(view),
  mode_("pen"),
  color_("#000000"),
  keyboard_(false),
  font_size_(24)
{
}

QColor Core::selectColor(QColor color)
{
  return QColorDialog::getColor(color);
}

void Core::emulateKeyPress(int key, int modifiers, const QString &text) const
{
  KeyboardModifiers md = KeyboardModifiers(modifiers);
  QKeyEvent *event = new QKeyEvent(QEvent::KeyPress, key, md, text);
  QApplication::postEvent(QApplication::focusWidget(), event);
}

void Core::setMode(const QString &mode)
{
  mode_ = mode;
  emit updateMode();
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
