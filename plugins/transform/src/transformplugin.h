/*
 * Copyright (C) 2014 Michael Kulabuhov, Kemerovo, Russia.
 *
 * See the LICENSE file for terms of use.
 */

#ifndef TRANSFORMPLUGIN_H
#define TRANSFORMPLUGIN_H

#include <QObject>
#include "iplugin.h"

class TransformPlugin : public QObject, IPlugin
{
  Q_OBJECT
  Q_PLUGIN_METADATA(IID "board.transform")
  Q_INTERFACES(IPlugin)
  Q_DISABLE_COPY_MOVE(TransformPlugin)
public:
  explicit TransformPlugin(QObject *parent = nullptr);
  ~TransformPlugin() override = default;
  void init() override;
};

#endif // TRANSFORMPLUGIN_H
