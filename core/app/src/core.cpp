/*
 * Copyright (C) 2012 Michael Kulabuhov, Kemerovo, Russia.
 *
 * See the LICENSE file for terms of use.
 */

#include <set>
#include <QGuiApplication>
#include <QKeyEvent>
#include <QtQml>
#include <quazip5/quazipfile.h>
#include "global.h"
#include "brd/brdstore.h"
#include "brd/brdnetworkaccessmanagerfactory.h"
#include "paint/paint.h"
#include "paint/sheetcanvas.h"
#include "paint/textwrapper.h"
#include "paint/textedittool.h"
#include "paint/imagewrapper.h"
#include "paint/videoplayer.h"
#include "style.h"
#include "paneltool.h"
#include "core.h"

bool openBookBrd(const QString &file_name);
bool openBookFiles(QuaZip *zip);
void saveBookBrd(const QString &file_name);
void saveBookFiles(QuaZip *zip);

Core::Core(QQmlEngine *engine, bool window_mode) :
  QObject(),
  _engine(engine),
  _main_window(nullptr),
  _window_mode(window_mode),
  _keyboard(false),
  _transparent(false),
  _map_componenet(),
  _panels(),
  _tools(),
  _sheets(),
  _plugins(),
  _importers(),
  _exporters(),
  _changes(false)
{
  _root_dir = QDir(QStandardPaths::writableLocation(QStandardPaths::ConfigLocation));
  _root_dir.mkdir("board");
  _root_dir.cd("board");
  _settings = new QSettings(_root_dir.filePath("settings.ini"), QSettings::IniFormat, this);
  _brdStore = new BrdStore(this);

  engine->setNetworkAccessManagerFactory(new BrdNetworkAccessManagerFactory(_brdStore, this));
  qmlRegisterType<Core>();
  qmlRegisterType<Paint>();
  qmlRegisterType<ToolInfo>();
  qmlRegisterType<Tool>();
  qmlRegisterType<Panel>();
  qmlRegisterType<Importer>();
  qmlRegisterType<Exporter>();
  qmlRegisterType<TextEditTool>();
  qmlRegisterType<Style>("board.core", 2, 0, "StyleQml");
  qmlRegisterType<PanelTool>("board.core", 2, 0, "PanelTool");
  qmlRegisterType<Sheet>("board.core.paint", 2, 0, "Sheet");
  qmlRegisterType<SheetCanvas>("board.core.paint", 2, 0, "SheetCanvas");
  qmlRegisterType<TextWrapper>("board.core.paint", 2, 0, "TextWrapper");
  qmlRegisterType<ImageWrapper>("board.core.paint", 2, 0, "ImageWrapper");
  qmlRegisterType<VideoPlayer>("board.core.paint", 2, 0, "VideoPlayer");

  _paint = new Paint(this);
  TextEditTool *text_edit_tool = new TextEditTool(_paint, this);
  auto context = engine->rootContext();
  context->setContextProperty("Core", this);
  context->setContextProperty("Paint", _paint);
  context->setContextProperty("TextEditTool", text_edit_tool);

  QQmlComponent *comp_style = getComponent("qrc:/core/qml/StyleQml.qml");
  Q_ASSERT(comp_style);
  QObject *style = comp_style->create();
  Q_ASSERT(style);
  context->setContextProperty("Style", style);

  _comp_sheet = getComponent("qrc:/core/qml/Sheet.qml");
  Q_ASSERT(_comp_sheet);

  registerImporter("Book files", "brd", openBookBrd);
  registerExporter("Book files", "brd", saveBookBrd);

  loadPlugins();
}

QWindow *Core::mainWindow()
{
  return _main_window;
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

void Core::registerTool(const QString &name, const QString &section, QQmlComponent *component, int width, int height)
{
  _tools.insert(name, new ToolInfo(name, section, component, width, height));
}

void Core::registerImporter(const QString &name, const QString &suffix, ImportFunc func)
{
  _importers.append(new Importer(name, suffix, func, this));
}

void Core::registerExporter(const QString &name, const QString &suffix, ExportFunc func)
{
  _exporters.append(new Exporter(name, suffix, func, this));
}

ISheet *Core::addSheet()
{
  Sheet *sheet = createSheet();
  _sheets.append(sheet);
  emit sheetsChanged();
  return sheet;
}

ISheet *Core::insertSheet(int index)
{
  Sheet *sheet = createSheet();
  _sheets.insert(index, sheet);
  emit sheetsChanged();
  return sheet;
}

void Core::deleteSheet(int index)
{
  Sheet *sheet = _sheets[index];
  sheet->deleteLater();
  _sheets.removeAt(index);
  emit sheetsChanged();
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

void Core::init(QWindow *main_window, const QString &brd_file)
{
  Q_ASSERT(main_window);
  _main_window = main_window;
  _sheet_place = _main_window->findChild<QQuickItem*>("sheetPlace");
  Q_ASSERT(_sheet_place);
  initPlugins();
  loadPanels();
  if (!brd_file.isEmpty())
  {
    openBook(brd_file);
  }
  else
  {
    newBook();
  }
  emit sheetsChanged();
}

bool Core::windowMode() const
{
  return _window_mode;
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
  return it.value();
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

QQmlListProperty<Sheet> Core::sheetsProperty()
{
  auto count_func = [](QQmlListProperty<Sheet> *list)
  {
    Core *core = qobject_cast<Core*>(list->object);
    Q_ASSERT(core);
    return core->sheets().size();
  };
  auto at_func = [](QQmlListProperty<Sheet> *list, int index)
  {
    Core *core = qobject_cast<Core*>(list->object);
    Q_ASSERT(core);
    return core->sheets().at(index);
  };
  return QQmlListProperty<Sheet>(this, nullptr, count_func, at_func);
}

QList<ToolInfo *> Core::tools() const
{
  return _tools.values();
}

QQmlListProperty<ToolInfo> Core::toolsProperty()
{
  auto count_func = [](QQmlListProperty<ToolInfo> *list)
  {
    Core *core = qobject_cast<Core*>(list->object);
    Q_ASSERT(core);
    return core->tools().size();
  };
  auto at_func = [](QQmlListProperty<ToolInfo> *list, int index)
  {
    Core *core = qobject_cast<Core*>(list->object);
    Q_ASSERT(core);
    return core->tools().at(index);
  };
  return QQmlListProperty<ToolInfo>(this, nullptr, count_func, at_func);
}

QQmlListProperty<Panel> Core::panelsProperty()
{
  auto count_func = [](QQmlListProperty<Panel> *list)
  {
    Core *core = qobject_cast<Core*>(list->object);
    Q_ASSERT(core);
    return core->panels().size();
  };
  auto at_func = [](QQmlListProperty<Panel> *list, int index)
  {
    Core *core = qobject_cast<Core*>(list->object);
    Q_ASSERT(core);
    return core->panels().at(index);
  };
  return QQmlListProperty<Panel>(this, nullptr, count_func, at_func);
}

QQmlListProperty<Importer> Core::importersProperty()
{
  auto count_func = [](QQmlListProperty<Importer> *list)
  {
    Core *core = qobject_cast<Core*>(list->object);
    Q_ASSERT(core);
    return core->importers().size();
  };
  auto at_func = [](QQmlListProperty<Importer> *list, int index)
  {
    Core *core = qobject_cast<Core*>(list->object);
    Q_ASSERT(core);
    return core->importers().at(index);
  };
  return QQmlListProperty<Importer>(this, nullptr, count_func, at_func);
}

QQmlListProperty<Exporter> Core::exportersProperty()
{
  auto count_func = [](QQmlListProperty<Exporter> *list)
  {
    Core *core = qobject_cast<Core*>(list->object);
    Q_ASSERT(core);
    return core->exporters().size();
  };
  auto at_func = [](QQmlListProperty<Exporter> *list, int index)
  {
    Core *core = qobject_cast<Core*>(list->object);
    Q_ASSERT(core);
    return core->exporters().at(index);
  };
  return QQmlListProperty<Exporter>(this, nullptr, count_func, at_func);
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

void Core::newBook()
{
  clearBook();
  for (int i = 0; i < 5; ++i)
  {
    addSheet();
  }
}

void Core::saveBook(const QUrl &file_url)
{
  QString file_name = file_url.toLocalFile();
  QFileInfo file_info(file_name);
  if (file_info.suffix().isEmpty())
  {
    file_info.setFile(file_info.filePath() + ".brd");
    file_name = file_info.filePath();
  }
  QString suffix = file_info.suffix();
  bool found = false;
  for (Exporter *exporter : _exporters)
  {
    if (QString::compare(exporter->suffix(), suffix, Qt::CaseInsensitive) == 0)
    {
      found = true;
      exporter->func()(file_name);
      break;
    }
  }
  if (!found)
  {
    saveBookBrd(file_name);
  }
  _changes = false;
  emit hasChangesChanged();
}

void Core::openBook(const QUrl &file_url)
{
  QString file_name = file_url.toLocalFile();
  QFileInfo file_info(file_name);
  QString suffix = file_info.suffix();
  bool ok = false;
  bool found = false;
  clearBook();
  for (Importer *importer : _importers)
  {
    if (QString::compare(importer->suffix(), suffix, Qt::CaseInsensitive) == 0)
    {
      found = true;
      ok = importer->func()(file_name);
      break;
    }
  }
  if (!ok)
  {
    if (!found)
    {
      showError("Неизвестный формат файла");
    }
    newBook();
  }
  _changes = false;
  emit hasChangesChanged();
  emit sheetsChanged();
}

void Core::quitActions()
{
  savePanels();
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

void Core::clearBook()
{
  for (QQuickItem *sheet : _sheets)
  {
    sheet->setVisible(false);
    sheet->deleteLater();
  }
  _sheets.clear();
  _brdStore->clear();
}

void Core::loadPlugins()
{
  QDir dir = QDir(QCoreApplication::applicationDirPath());
  dir.cd("plugins");
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
        _plugins.append(plugin);
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
  emit toolsChanged();
  emit importersChanged();
  emit exportersChanged();
}

void Core::savePanels()
{
  int panel_count = _panels.size();
  _settings->beginWriteArray("Panel", panel_count);
  for (int i = 0; i < panel_count; ++i)
  {
    Panel *panel = _panels[i];
    _settings->setArrayIndex(i);
    _settings->setValue("x", panel->x());
    _settings->setValue("y", panel->y());
    _settings->setValue("color", panel->color());

    QList<Tool*> tools = panel->tools();
    int tool_count = tools.size();
    _settings->beginWriteArray("Tool", tool_count);
    for (int j = 0; j < tool_count; ++j)
    {
      Tool *tool = tools[j];
      _settings->setArrayIndex(j);
      _settings->setValue("name", tool->name());
      _settings->setValue("x", tool->x());
      _settings->setValue("y", tool->y());
    }
    _settings->endArray();
  }
  _settings->endArray();
}

void Core::loadPanels()
{
  int panel_count = _settings->beginReadArray("Panel");
  for (int i = 0; i < panel_count; ++i)
  {
    Panel *panel = new Panel(this);
    _settings->setArrayIndex(i);
    panel->setX(_settings->value("x").toReal());
    panel->setY(_settings->value("y").toReal());
    panel->setColor(_settings->value("color").value<QColor>());
    _panels.append(panel);

    int tool_count = _settings->beginReadArray("Tool");
    for (int j = 0; j < tool_count; ++j)
    {
      _settings->setArrayIndex(j);
      QString name = _settings->value("name").toString();
      auto it = _tools.find(name);
      if (it != _tools.cend())
      {
        Tool *tool = new Tool(it.value(), panel);
        tool->setX(_settings->value("x").toInt());
        tool->setY(_settings->value("y").toInt());
        panel->addTool(tool);
      }
    }
    _settings->endArray();
  }
  _settings->endArray();
  emit panelsChanged();
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

bool openBookBrd(const QString &file_name)
{
  QuaZip zip(file_name);
  if (!zip.open(QuaZip::mdUnzip))
  {
    g_core->showError(QString("Не удалось открыть %1: error %2").arg(file_name).arg(zip.getZipError()));
    return false;
  }
  return openBookFiles(&zip);
}

bool openBookFiles(QuaZip *zip)
{
  for (bool more = zip->goToFirstFile(); more; more = zip->goToNextFile())
  {
    QuaZipFile zip_file(zip);
    if (!zip_file.open(QIODevice::ReadOnly))
    {
      g_core->showError(QString("Не удалось открыть книгу: %1").arg(zip_file.getZipError()));
      return false;
    }
    if (zip->getCurrentFileName() != "_book.xml")
    {
      QByteArray data = zip_file.readAll();
      g_core->brdStore()->addObject(data);
    }
  }
  if (!zip->setCurrentFile("_book.xml"))
  {
    g_core->showError(QString("Не удалось открыть книгу: %1").arg(zip->getZipError()));
    return false;
  }
  QuaZipFile zip_file(zip);
  if (!zip_file.open(QIODevice::ReadOnly))
  {
    g_core->showError(QString("Не удалось открыть книгу: %1").arg(zip_file.getZipError()));
    return false;
  }
  QXmlStreamReader reader(&zip_file);
  reader.readNextStartElement();
  if (reader.name() != "book") goto error;
  reader.readNextStartElement();
  if (reader.name() != "sheets") goto error;
  while (reader.readNextStartElement())
  {
    if (reader.name() != "sheet") goto error;
    ISheet *sheet = g_core->addSheet();
    Sheet *sheet_obj = dynamic_cast<Sheet*>(sheet);
    Q_ASSERT(sheet_obj);
    sheet_obj->deserialize(&reader);
  }
  return true;
error:
  g_core->showError("Книга имеет неверный формат");
  return false;
}

void saveBookBrd(const QString &file_name)
{
  QuaZip zip(file_name);
  if (!zip.open(QuaZip::mdCreate))
  {
    g_core->showError(QString("Не удалось открыть %1: error %2").arg(file_name).arg(zip.getZipError()));
    return;
  }
  saveBookFiles(&zip);
}

void saveBookFiles(QuaZip *zip)
{
  QuaZipFile zip_file(zip);
  if (!zip_file.open(QIODevice::WriteOnly, QuaZipNewInfo("_book.xml")))
  {
    g_core->showError(QString("Не удалось соханить книгу: %1").arg(zip_file.getZipError()));
    return;
  }
  QSet<QString> brd_objects;
  QXmlStreamWriter writer(&zip_file);
  writer.writeStartDocument();
  writer.writeStartElement("book");
  writer.writeAttribute("version", QString::number(1));
  writer.writeStartElement("sheets");
  int count = g_core->sheetsCount();
  for (int i = 0; i < count; ++i)
  {
    ISheet *sheet = g_core->sheet(i);
    Sheet *sheet_obj = dynamic_cast<Sheet*>(sheet);
    Q_ASSERT(sheet_obj);
    sheet_obj->serialize(&writer, &brd_objects);
  }
  writer.writeEndElement();
  writer.writeEndElement();
  writer.writeEndDocument();
  zip_file.close();

  for (QString hash : brd_objects)
  {
    QByteArray data = g_core->brdStore()->getObject(hash);
    if (data.isEmpty()) continue;
    if (!zip_file.open(QIODevice::WriteOnly, QuaZipNewInfo(hash)))
    {
      g_core->showError(QString("Не удалось соханить книгу: %1").arg(zip_file.getZipError()));
      return;
    }
    zip_file.write(data);
    zip_file.close();
  }
}
