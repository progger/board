/*
 * Copyright (C) 2012 Kulabuhov Michail, Kemerovo, Russia.
 *
 * See the LICENSE file for terms of use.
 */

#include <QApplication>
#include <QTextCodec>
#include <QTextStream>
#include <QFile>
#include "global.h"
#include "mainview.h"

bool global_mode_opengl = false;
QString global_plugin = QString();
QStringList global_plugin_params = QStringList();

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
  QStringList args = QApplication::arguments();
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
      else if (param == "--opengl")
      {
        global_mode_opengl = true;
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
      global_plugin = param;
      global_plugin_params = args.mid(i + 1);
      break;
    }
  }
}

void setupApplication(QApplication &app)
{
  if (global_mode_opengl)
  {
    //app.setGraphicsSystem("opengl");
  }
}

int main(int argc, char *argv[])
{
  //QTextCodec::setCodecForCStrings(QTextCodec::codecForName("utf8"));
  QApplication app(argc, argv);
  parseCmd();
  setupApplication(app);
  MainView view;
  view.showFullScreen();
  return app.exec();
}
