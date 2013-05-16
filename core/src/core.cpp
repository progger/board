/*
 * Copyright (C) 2012 Kulabuhov Michael, Kemerovo, Russia.
 *
 * See the LICENSE file for terms of use.
 */

#include <QGuiApplication>
#include <QKeyEvent>
#include <QtQml>
#include <QMessageBox>
#include "paint/paint.h"
#include "paint/sheetcanvas.h"
#include "paint/textwrapper.h"
#include "paint/imagewrapper.h"
#include "core.h"

Core::Core(QQuickView *parent) :
  QObject(parent),
  _keyboard(false)
{
  _root_dir = QDir::home();
  _root_dir.mkdir("board");
  _root_dir.cd("board");
  _settings = new QSettings(_root_dir.filePath("settings.ini"), QSettings::IniFormat, this);
  qmlRegisterType<Core>();
  qmlRegisterType<SheetCanvas>("board.core.paint", 1, 0, "SheetCanvas");
  qmlRegisterSingletonType<Paint>("board.core.paint", 1, 0, "Paint",
                                  [](QQmlEngine *, QJSEngine *) { return (QObject*) new Paint(); });
  qmlRegisterType<TextWrapper>("board.core.paint", 1, 0, "TextWrapper");
  qmlRegisterType<ImageWrapper>("board.core.paint", 1, 0, "ImageWrapper");
  auto context = parent->rootContext();
  context->setContextProperty("Core", this);
}

void Core::showError(const QString &error)
{
  QMessageBox::critical(nullptr, "Error", error);
}

void Core::emulateKeyPress(int key, int modifiers, const QString &text) const
{
  Qt::KeyboardModifiers md(modifiers);
  QKeyEvent *event = new QKeyEvent(QEvent::KeyPress, key, md, text);
  QGuiApplication::postEvent(parent(), event);
}

void Core::quitButton()
{
  QGuiApplication::quit();
}

void Core::minimizeButton()
{
  QQuickView *view = qobject_cast<QQuickView*>(mainView());
  if (view)
  {
    //view->showMinimized();
    view->setWindowState(Qt::WindowMinimized);
  }
}

void Core::setKeyboard(bool keyboard)
{
  _keyboard = keyboard;
  emit updateKeyboard();
}