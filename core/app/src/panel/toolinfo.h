/*
 * Copyright (C) 2014 Michael Kulabuhov, Kemerovo, Russia.
 *
 * See the LICENSE file for terms of use.
 */

#ifndef TOOLINFO_H
#define TOOLINFO_H

#include <QQuickItem>
#include <QQmlComponent>

class ToolInfo : public QObject
{
  Q_OBJECT
  Q_PROPERTY(QString name READ name CONSTANT)
  Q_PROPERTY(QString section READ section CONSTANT)
  Q_PROPERTY(int width READ width CONSTANT)
  Q_PROPERTY(int height READ height CONSTANT)
public:
  ToolInfo(const QString &name, const QString &section, QQmlComponent *component, int width, int height, QObject *parent = 0);
  QString name() const { return _name; }
  QString section() const { return _section; }
  QQmlComponent *component() const  { return _component; }
  int width() const { return _width; }
  int height() const { return _height; }
  Q_INVOKABLE void create(QQuickItem *parent);
private:
  const QString _name;
  const QString _section;
  QQmlComponent *_component;
  const int _width;
  const int _height;
};

#endif // TOOLINFO_H
