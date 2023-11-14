/*
 * Copyright (C) 2015 Michael Kulabuhov, Kemerovo, Russia.
 *
 * See the LICENSE file for terms of use.
 */

#ifndef IMPORTMIMIOPLUGIN_H
#define IMPORTMIMIOPLUGIN_H

#include <QObject>
#include "iplugin.h"

class ImportMimioPlugin : public QObject, IPlugin
{
  Q_OBJECT
  Q_PLUGIN_METADATA(IID "board.import-mimio")
  Q_INTERFACES(IPlugin)
  Q_DISABLE_COPY_MOVE(ImportMimioPlugin)
public:
  explicit ImportMimioPlugin(QObject *parent = nullptr);
  ~ImportMimioPlugin() override = default;
  void init() override;
};

#endif // IMPORTMIMIOPLUGIN_H
