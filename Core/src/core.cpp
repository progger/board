/*
 * Copyright (C) 2012 Kulabuhov Michael, Kemerovo, Russia.
 *
 * See the LICENSE file for terms of use.
 */

#include <QApplication>
#include <QKeyEvent>
#include "core.h"
#include "mainview.h"

using namespace Qt;

Core::Core(MainView *view) :
  QObject(view),
  view_(view),
  menu_visible_(false),
  keyboard_(false)
{
}

void Core::emulateKeyPress(int key, int modifiers, const QString &text) const
{
  KeyboardModifiers md = KeyboardModifiers(modifiers);
  QKeyEvent *event = new QKeyEvent(QEvent::KeyPress, key, md, text);
  QApplication::postEvent(QApplication::focusWidget(), event);
}

void Core::setKeyboard(bool keyboard)
{
  keyboard_ = keyboard;
  emit updateKeyboard();
}

void Core::setMenuVisible(bool menu_visible)
{
  menu_visible_ = menu_visible;
  emit updateMenuVisible();
}
