/*
 * Copyright (C) 2012 Kulabuhov Michael, Kemerovo, Russia.
 *
 * See the LICENSE file for terms of use.
 */

#include <QGuiApplication>
#include <QKeyEvent>
#include <QtQml>
#include <QMessageBox>
#include "brd/brdstore.h"
#include "brd/brdnetworkaccessmanagerfactory.h"
#include "paint/paint.h"
#include "paint/sheetcanvas.h"
#include "paint/textwrapper.h"
#include "paint/imagewrapper.h"
#include "core.h"

int sheetsCountFunction(QQmlListProperty<QQuickItem> *list)
{
  Core *core = qobject_cast<Core*>(list->object);
  Q_ASSERT(core);
  return core->sheets()->size();
}

QQuickItem *sheetsAtFunction(QQmlListProperty<QQuickItem> *list, int index)
{
  Core *core = qobject_cast<Core*>(list->object);
  Q_ASSERT(core);
  return core->sheets()->at(index);
}

Core::Core(QQuickView *parent) :
  QObject(parent),
  _keyboard(false),
  _map_componenet(),
  _sheets()
{
  _root_dir = QDir::home();
  _root_dir.mkdir("board");
  _root_dir.cd("board");
  _settings = new QSettings(_root_dir.filePath("settings.ini"), QSettings::IniFormat, this);
  _brdStore = new BrdStore(this);

  parent->engine()->setNetworkAccessManagerFactory(new BrdNetworkAccessManagerFactory(_brdStore, this));
  qmlRegisterType<Core>();
  qmlRegisterType<Paint>();
  qmlRegisterType<SheetCanvas>("board.core.paint", 1, 0, "SheetCanvas");
  qmlRegisterType<TextWrapper>("board.core.paint", 1, 0, "TextWrapper");
  qmlRegisterType<ImageWrapper>("board.core.paint", 1, 0, "ImageWrapper");

  _paint = new Paint(this);
  auto context = parent->rootContext();
  context->setContextProperty("Core", this);
  context->setContextProperty("Paint", _paint);

  _comp_sheet = getComponent("qrc:/core/qml/Sheet.qml");
  connect(parent, SIGNAL(statusChanged(QQuickView::Status)), SLOT(onMainViewStatusChanged(QQuickView::Status)));
}

void Core::showError(const QString &error)
{
  QMessageBox::critical(nullptr, "Error", error);
}

QQmlComponent *Core::getComponent(const QString &urlString)
{
  auto it = _map_componenet.find(urlString);
  if (it == _map_componenet.cend())
  {
    QQuickView *view = qobject_cast<QQuickView*>(parent());
    Q_ASSERT(view);
    QQmlComponent *component = new QQmlComponent(view->engine(), QUrl(urlString), this);
    _map_componenet[urlString] = component;
    return component;
  }
  return (*it).second;
}

QQmlListProperty<QQuickItem> Core::sheetsProperty()
{
  return QQmlListProperty<QQuickItem>(this, nullptr, sheetsCountFunction, sheetsAtFunction);
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

void Core::onMainViewStatusChanged(QQuickView::Status status)
{
  if (status == QQuickView::Loading) return;
  Q_ASSERT(status == QQuickView::Ready);
  QQuickView *view = qobject_cast<QQuickView*>(parent());
  Q_ASSERT(view);
  Q_ASSERT(view->rootObject());
  _sheet_place = view->rootObject()->findChild<QQuickItem*>("sheetPlace");
  Q_ASSERT(_sheet_place);
  for (int i = 0; i < 5; ++i)
  {
    QQuickItem *sheet = qobject_cast<QQuickItem*>(_comp_sheet->create());
    Q_ASSERT(sheet);
    sheet->setParent(_sheet_place);
    sheet->setVisible(false);
    sheet->setParentItem(_sheet_place);
    _sheets.push_back(sheet);
  }
  emit sheetsChanged();
}

void Core::setKeyboard(bool keyboard)
{
  _keyboard = keyboard;
  emit keyboardChanged();
}
