/*
 * Copyright (C) 2013 Michael Kulabuhov, Kemerovo, Russia.
 *
 * See the LICENSE file for terms of use.
 */

#ifndef IMPORTDOCPLUGIN_H
#define IMPORTDOCPLUGIN_H

#include <QObject>
#include "iplugin.h"

class ImportDocPlugin : public QObject, IPlugin
{
  Q_OBJECT
  Q_PLUGIN_METADATA(IID "board.import-documents")
  Q_INTERFACES(IPlugin)
  Q_DISABLE_COPY_MOVE(ImportDocPlugin)
public:
  explicit ImportDocPlugin(QObject *parent = nullptr);
  ~ImportDocPlugin() override = default;
  void init() override;
};

#endif // IMPORTDOCPLUGIN_H
