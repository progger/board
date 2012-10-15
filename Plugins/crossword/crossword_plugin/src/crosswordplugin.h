/*
 * Copyright (C) 2012 Kulabuhov Michael, Kemerovo, Russia.
 *
 * See the LICENSE file for terms of use.
 */

#ifndef CROSSWORDPLUGIN_H
#define CROSSWORDPLUGIN_H

#include <QObject>
#include "iplugin.h"

class CrosswordPlugin : public QObject, public IPlugin
{
  Q_OBJECT
  Q_INTERFACES(IPlugin)
public:
  virtual ~CrosswordPlugin() {}
  virtual void init(ICore *core, const QStringList &param);
};

#endif // CROSSWORDPLUGIN_H
