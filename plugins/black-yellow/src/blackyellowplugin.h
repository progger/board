/*
 * Copyright (C) 2014 Michael Kulabuhov, Kemerovo, Russia.
 *
 * See the LICENSE file for terms of use.
 */

#ifndef BLACKYELLOWPLUGIN_H
#define BLACKYELLOWPLUGIN_H

#include <QObject>
#include "iplugin.h"

class BlackYellowPlugin : public QObject, IPlugin
{
  Q_OBJECT
  Q_PLUGIN_METADATA(IID "board.blackyellow")
  Q_INTERFACES(IPlugin)
  Q_DISABLE_COPY_MOVE(BlackYellowPlugin)
public:
  explicit BlackYellowPlugin(QObject *parent = nullptr);
  ~BlackYellowPlugin() override = default;
  void init() override;
};

#endif // BLACKYELLOWPLUGIN_H
