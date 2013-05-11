/*
 * Copyright (C) 2012 Kulabuhov Michael, Kemerovo, Russia.
 *
 * See the LICENSE file for terms of use.
 */

#include <QGuiApplication>
#include <QKeyEvent>
#include <QtQml>
#include "paint/paint.h"
#include "paint/sheetcanvas.h"
#include "paint/textwrapper.h"
#include "core.h"

using namespace Qt;

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
  auto context = parent->rootContext();
  context->setContextProperty("Core", this);
}

void Core::showError(const QString &error)
{
  Q_UNUSED(error);
  //TODO
  //QMessageBox::critical(qobject_cast<QWidget*>(mainView()), "Error", error);
}

void Core::emulateKeyPress(int key, int modifiers, const QString &text) const
{
  Q_UNUSED(key);
  Q_UNUSED(modifiers);
  Q_UNUSED(text);
  //TODO
  /*
  KeyboardModifiers md = KeyboardModifiers(modifiers);
  QKeyEvent *event = new QKeyEvent(QEvent::KeyPress, key, md, text);
  QApplication::postEvent(QApplication::focusWidget(), event);
  */
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
