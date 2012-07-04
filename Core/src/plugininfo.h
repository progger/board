/*
 * Copyright (C) 2012 Kulabuhov Michael, Kemerovo, Russia.
 *
 * See the LICENSE file for terms of use.
 */

#ifndef PLUGININFO_H
#define PLUGININFO_H

#include <QObject>
#include <QStringList>

class PluginInfo : public QObject
{
  Q_OBJECT
  Q_PROPERTY(QString image READ image NOTIFY updateImage)
  Q_PROPERTY(QObjectList children READ children NOTIFY updateChildren)
  Q_PROPERTY(QObject *parent READ parent)
  Q_PROPERTY(bool isDir READ isDir)

public:
  explicit PluginInfo(QObject *parent, const QString &name);
  QString image() { return image_; }
  QString pluginName() { return plugin_name_; }
  QStringList pluginParam() { return plugin_param_; }
  bool isDir();

signals:
  void updateImage();
  void updateChildren();

public slots:
  void setImage(const QString &image);
  void setPluginName(const QString &plugin_name);
  void setPluginParam(const QStringList &plugin_param);

private:
  QString image_;
  QString plugin_name_;
  QStringList plugin_param_;
};

#endif // PLUGININFO_H
