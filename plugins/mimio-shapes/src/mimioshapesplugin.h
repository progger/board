/*
 * Copyright (C) 2015 Michael Kulabuhov, Kemerovo, Russia.
 *
 * See the LICENSE file for terms of use.
 */

#ifndef MIMIOSHAPESPLUGIN_H
#define MIMIOSHAPESPLUGIN_H

#include <QObject>
#include "iplugin.h"

class MimioShapesPlugin : public QObject, IPlugin
{
  Q_OBJECT
  Q_PLUGIN_METADATA(IID "board.mimio-shapes")
  Q_INTERFACES(IPlugin)
  Q_DISABLE_COPY_MOVE(MimioShapesPlugin)
public:
  explicit MimioShapesPlugin(QObject *parent = nullptr);
  ~MimioShapesPlugin() override = default;
  void init() override;
};

#endif // MIMIOSHAPESPLUGIN_H
