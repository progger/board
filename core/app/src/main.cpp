/*
 * Copyright (C) 2012 Michael Kulabuhov, Kemerovo, Russia.
 *
 * See the LICENSE file for terms of use.
 */

#include <QApplication>
#include <QQmlEngine>
#include <QWindow>
#include <QTextStream>
#include <QFile>
#include "global.h"
#include "core.h"

void help()
{
  QTextStream cout(stdout);
  QFile help_file(":/core/res/help");
  if (help_file.open(QIODevice::ReadOnly))
  {
    cout << help_file.readAll();
  }
  cout.flush();
  exit(EXIT_SUCCESS);
}

void parseCmd(QString &brd_file, bool &window_mode)
{
  QStringList args = QCoreApplication::arguments();
  int count = args.count();
  for (int i = 1; i < count; i++)
  {
    QString param = args.at(i);
    if (param.startsWith('-'))
    {
      if (param == "--help" || param == "-h")
      {
        help();
      }
      else if (param == "--window" || param == "-w")
      {
        window_mode = true;
      }
      else if (param == "--fullscreen" || param == "-f")
      {
        window_mode = false;
      }
      else
      {
        QTextStream cout(stdout);
        cout << "Invalid argument: " << param << Qt::endl;
        help();
      }
    }
    else
    {
      if (brd_file.isEmpty())
      {
        brd_file = param;
      }
    }
  }
}

int main(int argc, char *argv[])
{
  QApplication app(argc, argv);
  QString brd_file;
  bool window_mode = true;
  parseCmd(brd_file, window_mode);

  QQmlEngine *engine = new QQmlEngine();
  Core *core = new Core(engine, window_mode);
  g_core = core;
  QQuickWindow::setDefaultAlphaBuffer(true);
  QQmlComponent *component = core->getComponent("qrc:/core/qml/Board.qml");
  if (!component)
  {
    return EXIT_FAILURE;
  }
  QObject *obj = component->create();
  Q_ASSERT(obj);
  QWindow *main_window = qobject_cast<QWindow*>(obj);
  Q_ASSERT(main_window);

  core->init(main_window, brd_file);
  if (window_mode)
    main_window->showMaximized();
  else
    main_window->showFullScreen();
  int result = app.exec();
  core->quitActions();
  delete obj;
  delete engine;
  delete core;
  return result;
}
