/*
 * Copyright (C) 2012 Kulabuhov Michael, Kemerovo, Russia.
 *
 * See the LICENSE file for terms of use.
 */

#ifndef MENUITEM_H
#define MENUITEM_H

#include <QObject>
#include <QStringList>

class MenuItem : public QObject
{
  Q_OBJECT
  Q_PROPERTY(QString name READ name CONSTANT FINAL)
  Q_PROPERTY(QString image READ image CONSTANT FINAL)
  Q_PROPERTY(QObjectList children READ children CONSTANT FINAL)
  Q_PROPERTY(bool isDir READ isDir CONSTANT FINAL)

public:
  explicit MenuItem(QObject *parent, const QString &name, const QString &image,
                    const QString &plugin_name, const QStringList &plugin_param);
  QString name() { return name_; }
  QString image() { return image_; }
  QString pluginName() { return plugin_name_; }
  QStringList pluginParam() { return plugin_param_; }
  bool isDir() { return plugin_name_.isEmpty(); }

private:
  QString name_;
  QString image_;
  QString plugin_name_;
  QStringList plugin_param_;
};

#endif // MENUITEM_H
