/*
 * Copyright (C) 2014 Michael Kulabuhov, Kemerovo, Russia.
 *
 * See the LICENSE file for terms of use.
 */

#ifndef CATEGORIESPLUGIN_H
#define CATEGORIESPLUGIN_H

#include <QObject>
#include "iplugin.h"

class CategoriesPlugin : public QObject, IPlugin
{
  Q_OBJECT
  Q_PLUGIN_METADATA(IID "board.categories")
  Q_INTERFACES(IPlugin)
  Q_DISABLE_COPY_MOVE(CategoriesPlugin)
public:
  explicit CategoriesPlugin(QObject *parent = nullptr);
  ~CategoriesPlugin() override = default;
  void init() override;
};

#endif // CATEGORIESPLUGIN_H
