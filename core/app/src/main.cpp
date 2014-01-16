/*
 * Copyright (C) 2012 Michael Kulabuhov, Kemerovo, Russia.
 *
 * See the LICENSE file for terms of use.
 */

#include <QApplication>
#include <QQmlEngine>
#include <QQuickWindow>
#include <QTextStream>
#include <QFile>
#include <qpa/qplatformnativeinterface.h>
#include "global.h"
#include "mpxeventfilter.h"
#include "core.h"
#include <X11/X.h>
#include <X11/extensions/XInput2.h>

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

  QQmlEngine engine;
  Core *core = new Core(&engine);
  g_core = core;
  QQuickWindow::setDefaultAlphaBuffer(true);
  QQmlComponent *component = core->getComponent("qrc:/core/qml/Board.qml");
  if (!component)
  {
    return EXIT_FAILURE;
  }
  QObject *obj = component->create();
  obj->setParent(core);
  Q_ASSERT(obj);
  QQuickWindow *main_window = qobject_cast<QQuickWindow*>(obj);
  Q_ASSERT(main_window);

  Display *display = static_cast<Display *>(app.platformNativeInterface()->nativeResourceForWindow("display", main_window));
  app.installNativeEventFilter(new MpxEventFilter(main_window));
  XIEventMask eventmask;
  unsigned char mask[1] = { 0 };
  eventmask.deviceid = XIAllMasterDevices;
  eventmask.mask_len = sizeof(mask);
  eventmask.mask = mask;
  XISetMask(mask, XI_Motion);
  XISetMask(mask, XI_ButtonPress);
  XISetMask(mask, XI_ButtonRelease);
  XISelectEvents(display, main_window->winId(), &eventmask, 1);

  core->init(main_window);
  if (g_window_mode)
    main_window->showMaximized();
  else
    main_window->showFullScreen();
  int result = app.exec();
  delete obj;  //TODO: разобраться почему без этого завершается некорректно
  return result;
}
