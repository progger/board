/*
 * Copyright (C) 2012 Michael Kulabuhov, Kemerovo, Russia.
 *
 * See the LICENSE file for terms of use.
 */

#include <set>
#include <QGuiApplication>
#include <QKeyEvent>
#include <QtQml>
#include "global.h"
#include "quazipfile.h"
#include "brd/brdstore.h"
#include "brd/brdnetworkaccessmanagerfactory.h"
#include "paint/paint.h"
#include "paint/sheetcanvas.h"
#include "paint/textwrapper.h"
#include "paint/imagewrapper.h"
#include "paint/videoplayer.h"
#include "style.h"
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

Core::Core(QQmlEngine *engine) :
  QObject(engine),
  _engine(engine),
  _main_window(nullptr),
  _keyboard(false),
  _transparent(false),
  _map_componenet(),
  _sheets(),
  _changes(false)
{
  _root_dir = QDir::home();
  _root_dir.mkdir("board");
  _root_dir.cd("board");
  _settings = new QSettings(_root_dir.filePath("settings.ini"), QSettings::IniFormat, this);
  _brdStore = new BrdStore(this);

  engine->setNetworkAccessManagerFactory(new BrdNetworkAccessManagerFactory(_brdStore, this));
  qmlRegisterType<Core>();
  qmlRegisterType<Paint>();
  qmlRegisterType<Style>("board.core", 2, 0, "StyleQml");
  qmlRegisterType<Sheet>("board.core.paint", 2, 0, "Sheet");
  qmlRegisterType<SheetCanvas>("board.core.paint", 2, 0, "SheetCanvas");
  qmlRegisterType<TextWrapper>("board.core.paint", 2, 0, "TextWrapper");
  qmlRegisterType<ImageWrapper>("board.core.paint", 2, 0, "ImageWrapper");
  qmlRegisterType<VideoPlayer>("board.core.paint", 2, 0, "VideoPlayer");
  qmlRegisterSingletonType<Style>("board.core", 2, 0, "Style",
                                  [](QQmlEngine *, QJSEngine *)
  {
    return g_core->getComponent("qrc:/core/qml/StyleQml.qml")->create();
  });

  _paint = new Paint(this);
  auto context = engine->rootContext();
  context->setContextProperty("Core", this);
  context->setContextProperty("Paint", _paint);

  _comp_sheet = getComponent("qrc:/core/qml/Sheet.qml");
  Q_ASSERT(_comp_sheet);

  loadPlugins();
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
  logError(error);
  emit errorMessageBox(error);
}

void Core::addPluginRowItem(const QString &url_string)
{
  QQmlComponent *component = getComponent(url_string);
  if (!component) return;
  QQuickItem *item = qobject_cast<QQuickItem*>(component->create());
  if (!item) return;
  item->setParent(_plugin_row);
  item->setParentItem(_plugin_row);
  item->setHeight(_plugin_row->height());
}

void Core::setChanges()
{
  _changes = true;
  emit hasChangesChanged();
}

bool Core::hasChanges()
{
  return _changes;
}

void Core::init(QWindow *main_window)
{
  Q_ASSERT(main_window);
  _main_window = main_window;
  _sheet_place = _main_window->findChild<QQuickItem*>("sheetPlace");
  Q_ASSERT(_sheet_place);
  _plugin_row = _main_window->findChild<QQuickItem*>("pluginRow");
  Q_ASSERT(_plugin_row);
  initPlugins();
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

bool Core::windowMode() const
{
  return g_window_mode;
}

QQmlComponent *Core::getComponent(const QString &url_string)
{
  auto it = _map_componenet.find(url_string);
  if (it == _map_componenet.cend())
  {
    QQmlComponent *component = new QQmlComponent(_engine, QUrl(url_string), this);
    if (!component->isReady())
    {
      logError("Error loading component " + url_string + " : " + component->errorString());
      component = nullptr;
    }
    _map_componenet[url_string] = component;
    return component;
  }
  return (*it).second;
}

void Core::logMessage(const QString &message)
{
  QTextStream cout(stdout);
  cout << message << endl;
}

void Core::logError(const QString &error)
{
  QTextStream cerr(stderr);
  cerr << error << endl;
}

QQmlListProperty<QQuickItem> Core::sheetsProperty()
{
  return QQmlListProperty<QQuickItem>(this, nullptr, sheetsCountFunction, sheetsAtFunction);
}

void Core::emulateKeyPress(int key, int modifiers, const QString &text) const
{
  Qt::KeyboardModifiers md(modifiers);
  QKeyEvent *event = new QKeyEvent(QEvent::KeyPress, key, md, text);
  QGuiApplication::postEvent(_main_window, event);
}

void Core::quitButton()
{
  QGuiApplication::postEvent(_main_window, new QCloseEvent());
}

void Core::minimizeButton()
{
  _main_window->showMinimized();
}

void Core::saveBook(const QString &file_name)
{
  QFileInfo file_info(file_name);
  if (file_info.suffix().isEmpty())
  {
    file_info.setFile(file_info.filePath() + ".brd");
  }
  QuaZip zip(file_info.filePath());
  if (!zip.open(QuaZip::mdCreate))
  {
    showError(QString("Не удалось открыть %1: error %2").arg(file_name).arg(zip.getZipError()));
    return;
  }
  saveBookFiles(&zip);
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
    sheet->setVisible(false);
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
  _changes = false;
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

void Core::loadPlugins()
{
#if defined(Q_OS_LINUX) && !defined(QT_DEBUG)
  QDir dir("/usr/lib/board");
#else
  QDir dir = QDir(QCoreApplication::applicationDirPath());
  dir.cd("plugins");
#endif
  QStringList files = dir.entryList(QDir::Files);
  for (QString file_name : files)
  {
    QString full_file_name = dir.absoluteFilePath(file_name);
    QPluginLoader *loader = new QPluginLoader(full_file_name, this);
    QObject *plugin_obj = loader->instance();
    if (plugin_obj)
    {
      IPlugin *plugin = qobject_cast<IPlugin*>(plugin_obj);
      if (plugin)
      {
        _plugins.push_back(plugin);
      }
      else
      {
        logError("Invalid plugin interface " + full_file_name);
      }
    }
    else
    {
      logError("Error loading plugin " + full_file_name + " : " + loader->errorString());
    }
  }
}

void Core::initPlugins()
{
  for (IPlugin *plugin : _plugins)
  {
    plugin->init();
  }
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
