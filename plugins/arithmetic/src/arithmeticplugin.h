/*
 * Copyright (C) 2014 Michael Kulabuhov, Kemerovo, Russia.
 *
 * See the LICENSE file for terms of use.
 */

#ifndef ARITHMETICPLUGIN_H
#define ARITHMETICPLUGIN_H

#include <QObject>
#include "iplugin.h"

class ArithmeticPlugin : public QObject, IPlugin
{
  Q_OBJECT
  Q_PLUGIN_METADATA(IID "board.arithmetic")
  Q_INTERFACES(IPlugin)
  Q_DISABLE_COPY_MOVE(ArithmeticPlugin)
public:
  explicit ArithmeticPlugin(QObject *parent = nullptr);
  ~ArithmeticPlugin() override = default;
  void init() override;
};

#endif // ARITHMETICPLUGIN_H
