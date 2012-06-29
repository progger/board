/*
 * Copyright (C) 2012 Kulabuhov Michael, Kemerovo, Russia.
 *
 * See the LICENSE file for terms of use.
 */

#ifndef PLUGININFO_H
#define PLUGININFO_H

#include <QObject>
#include "iplugininfo.h"

class PluginInfo : public QObject
{
  Q_OBJECT
  Q_PROPERTY(QString name READ name NOTIFY updateName)
  Q_PROPERTY(QString image READ image NOTIFY updateImage)

public:
  explicit PluginInfo(IPluginInfo *plugin_info, QString &lib_name, QObject *parent = 0);
  QString name();
  QString image();
  QString libName() { return lib_name_; }

signals:
  void updateName();
  void updateImage();

private:
  IPluginInfo *plugin_info_;
  QString lib_name_;

};

#endif // PLUGININFO_H
