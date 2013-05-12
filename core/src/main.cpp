/*
 * Copyright (C) 2012 Kulabuhov Michail, Kemerovo, Russia.
 *
 * See the LICENSE file for terms of use.
 */

#include <QApplication>
#include <QTextCodec>
#include <QTextStream>
#include <QFile>
#include "mainview.h"

void help()
{
  QTextStream cout(stdout);
  QFile help_file("qrc:/core/res/help");
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
      if (param == "--help")
      {
        help();
      }
      else
      {
        QTextStream cout(stdout);
        cout << "Invalid argument: " << param << endl;
        help();
      }
    }
  }
}

int main(int argc, char *argv[])
{
  QApplication app(argc, argv);
  parseCmd();
  MainView view;
  view.showFullScreen();
  return app.exec();
}
