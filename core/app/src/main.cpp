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

void parseCmd()
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
        g_window_mode = true;
      }
      else if (param == "--fullscreen" || param == "-f")
      {
        g_window_mode = false;
      }
      else
      {
        QTextStream cout(stdout);
        cout << "Invalid argument: " << param << endl;
        help();
      }
    }
    else
    {
      if (g_brd_file.isEmpty())
      {
        g_brd_file = param;
      }
    }
  }
}

int main(int argc, char *argv[])
{
  QApplication app(argc, argv);
  parseCmd();

  QQmlEngine *engine = new QQmlEngine();
  Core *core = new Core(engine);
  g_core = core;
  QQuickWindow::setDefaultAlphaBuffer(true);
  QQmlComponent *component = core->getComponent("qrc:/core/qml/Board.qml");
  if (!component)
  {
    return EXIT_FAILURE;
  }
  QObject *obj = component->create();
  Q_ASSERT(obj);
  g_main_window = qobject_cast<QWindow*>(obj);
  Q_ASSERT(g_main_window);

  core->init(g_main_window);
  if (g_window_mode)
    g_main_window->showMaximized();
  else
    g_main_window->showFullScreen();
  int result = app.exec();
  delete obj;
  delete engine;
  delete core;
  return result;
}
