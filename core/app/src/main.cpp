/*
 * Copyright (C) 2012 Michael Kulabuhov, Kemerovo, Russia.
 *
 * See the LICENSE file for terms of use.
 */

#include <QApplication>
#include <QTextCodec>
#include <QTextStream>
#include <QFile>
#include "global.h"
#include "mainview.h"

void help()
{
  QTextStream cout(stdout);
  QFile help_file(":/core/res/help");
  if (help_file.open(QIODevice::ReadOnly))
  {
    cout << help_file.readAll();
  }
  cout.flush();
  exit(0);
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
  MainView view;
  QSurfaceFormat format = view.format();
  format.setAlphaBufferSize(8);
  view.setFormat(format);
  view.setColor(QColor(0, 0, 0, 0));
  if (g_window_mode)
    view.showMaximized();
  else
    view.showFullScreen();
  return app.exec();
}
