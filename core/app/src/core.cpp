/*
 * Copyright (C) 2012 Kulabuhov Michael, Kemerovo, Russia.
 *
 * See the LICENSE file for terms of use.
 */

#include <set>
#include <QGuiApplication>
#include <QKeyEvent>
#include <QtQml>
#include <QMessageBox>
#include <QFileDialog>
#include "quazipfile.h"
#include "brd/brdstore.h"
#include "brd/brdnetworkaccessmanagerfactory.h"
#include "paint/paint.h"
#include "paint/sheetcanvas.h"
#include "paint/textwrapper.h"
#include "paint/imagewrapper.h"
#include "paint/videoplayer.h"
#include "global.h"
#include "core.h"

using namespace std;

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
  _transparent(false),
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
  qmlRegisterType<Sheet>("board.core.paint", 2, 0, "Sheet");
  qmlRegisterType<SheetCanvas>("board.core.paint", 2, 0, "SheetCanvas");
  qmlRegisterType<TextWrapper>("board.core.paint", 2, 0, "TextWrapper");
  qmlRegisterType<ImageWrapper>("board.core.paint", 2, 0, "ImageWrapper");
  qmlRegisterType<VideoPlayer>("board.core.paint", 2, 0, "VideoPlayer");

  _paint = new Paint(this);
  auto context = parent->rootContext();
  context->setContextProperty("Core", this);
  context->setContextProperty("Paint", _paint);

  _comp_sheet = getComponent("qrc:/core/qml/Sheet.qml");
  connect(parent, SIGNAL(statusChanged(QQuickView::Status)), SLOT(onMainViewStatusChanged(QQuickView::Status)));
}

QObject *Core::mainView()
{
  return parent();
}

QDir Core::rootDir()
{
  return _root_dir;
}

QSettings *Core::settings()
{
  return _settings;
}

IPaint *Core::paint()
{
  return _paint;
}

IBrdStore *Core::brdStore()
{
  return _brdStore;
}

int Core::sheetsCount()
{
  return _sheets.size();
}

int Core::sheetIndex()
{
  return _sheet_index;
}

ISheet *Core::sheet(int index)
{
  return _sheets[index];
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
    Q_ASSERT(component->isReady());
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

void Core::saveBook()
{
  QFileDialog dialog;
  dialog.setAcceptMode(QFileDialog::AcceptSave);
  dialog.setNameFilter("Book files (*.brd)");
  dialog.setDefaultSuffix("brd");
  if (!dialog.exec()) return;
  QString file_name = dialog.selectedFiles().first();
  saveBook(file_name);
}

void Core::saveBook(const QString &file_name)
{
  QuaZip zip(file_name);
  if (!zip.open(QuaZip::mdCreate))
  {
    showError(QString("Не удалось открыть %1: error %2").arg(file_name).arg(zip.getZipError()));
    return;
  }
  saveBookFiles(&zip);
}

void Core::openBook()
{
  QFileDialog dialog;
  dialog.setAcceptMode(QFileDialog::AcceptOpen);
  dialog.setNameFilter("Book files (*.brd)");
  dialog.setDefaultSuffix("brd");
  if (!dialog.exec()) return;
  QString file_name = dialog.selectedFiles().first();
  openBook(file_name);
}

void Core::openBook(const QString &file_name)
{
  QuaZip zip(file_name);
  if (!zip.open(QuaZip::mdUnzip))
  {
    showError(QString("Не удалось открыть %1: error %2").arg(file_name).arg(zip.getZipError()));
    return;
  }
  for (QQuickItem *sheet : _sheets)
  {
    sheet->deleteLater();
  }
  _sheets.clear();
  _brdStore->clear();
  openBookFiles(&zip);
  emit sheetsChanged();
}

void Core::insertSheet(int index)
{
  Sheet *sheet = createSheet();
  _sheets.insert(_sheets.begin() + index, sheet);
  emit sheetsChanged();
}

void Core::deleteSheet(int index)
{
  QQuickItem *sheet = _sheets[index];
  sheet->deleteLater();
  _sheets.erase(_sheets.begin() + index);
  emit sheetsChanged();
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
  if (!g_brd_file.isEmpty())
  {
    openBook(g_brd_file);
  }
  else
  {
    for (int i = 0; i < 5; ++i)
    {
      Sheet *sheet = createSheet();
      _sheets.push_back(sheet);
    }
  }
  emit sheetsChanged();
}

Sheet *Core::createSheet()
{
  Sheet *sheet = qobject_cast<Sheet*>(_comp_sheet->create());
  Q_ASSERT(sheet);
  sheet->setParent(_sheet_place);
  sheet->setVisible(false);
  sheet->setParentItem(_sheet_place);
  return sheet;
}

void Core::saveBookFiles(QuaZip *zip)
{
  QuaZipFile zip_file(zip);
  if (!zip_file.open(QIODevice::WriteOnly, QuaZipNewInfo("_book.xml")))
  {
    showError(QString("Не удалось соханить книгу: %1").arg(zip_file.getZipError()));
    return;
  }
  set<QString> brd_objects;
  QXmlStreamWriter writer(&zip_file);
  writer.writeStartDocument();
  writer.writeStartElement("book");
  writer.writeAttribute("version", "1.0");
  writer.writeStartElement("sheets");
  for (Sheet *sheet : _sheets)
  {
    SheetCanvas *canvas = sheet->canvasObj();;
    canvas->serializeSheet(&writer, &brd_objects);
  }
  writer.writeEndElement();
  writer.writeEndElement();
  writer.writeEndDocument();
  zip_file.close();

  for (QString hash : brd_objects)
  {
    QByteArray data = _brdStore->getObject(hash);
    if (data.isEmpty()) continue;
    if (!zip_file.open(QIODevice::WriteOnly, QuaZipNewInfo(hash)))
    {
      showError(QString("Не удалось соханить книгу: %1").arg(zip_file.getZipError()));
      return;
    }
    zip_file.write(data);
    zip_file.close();
  }
}

void Core::openBookFiles(QuaZip *zip)
{
  for(bool more = zip->goToFirstFile(); more; more = zip->goToNextFile())
  {
    QuaZipFile zip_file(zip);
    if (!zip_file.open(QIODevice::ReadOnly))
    {
      showError(QString("Не удалось открыть книгу: %1").arg(zip_file.getZipError()));
      return;
    }
    if (zip->getCurrentFileName() != "_book.xml")
    {
      QByteArray data = zip_file.readAll();
      _brdStore->addObject(data);
    }
  }
  if (!zip->setCurrentFile("_book.xml"))
  {
    showError(QString("Не удалось открыть книгу: %1").arg(zip->getZipError()));
    return;
  }
  QuaZipFile zip_file(zip);
  if (!zip_file.open(QIODevice::ReadOnly))
  {
    showError(QString("Не удалось открыть книгу: %1").arg(zip_file.getZipError()));
    return;
  }
  QXmlStreamReader reader(&zip_file);
  reader.readNextStartElement();
  if (reader.name() != "book" || reader.attributes().value("version") != "1.0") goto error;
  reader.readNextStartElement();
  if (reader.name() != "sheets") goto error;
  while (reader.readNextStartElement())
  {
    if (reader.name() != "sheet") goto error;
    Sheet *sheet = createSheet();
    _sheets.push_back(sheet);
    SheetCanvas *canvas = sheet->canvasObj();
    canvas->deserializeSheet(&reader);
  }
  return;
error:
  showError("Книга имеет неверный формат");
}

void Core::setKeyboard(bool keyboard)
{
  _keyboard = keyboard;
  emit keyboardChanged();
}

void Core::setTransparent(bool transparent)
{
  _transparent = transparent;
  emit transparentChanged();
}

void Core::setSheetIndex(int index)
{
  _sheet_index = index;
  emit sheetIndexChanged();
}
