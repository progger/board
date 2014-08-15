/*
 * Copyright (C) 2014 Michael Kulabuhov, Kemerovo, Russia.
 *
 * See the LICENSE file for terms of use.
 */

#ifndef TOOL_H
#define TOOL_H

#include <QObject>

class Tool : public QObject
{
  Q_OBJECT
  Q_PROPERTY(int x READ x WRITE setX NOTIFY xChanged)
  Q_PROPERTY(int y READ y WRITE setY NOTIFY yChanged)
public:
  Tool(const QString &name, const QString &section, const QString &url_string, QObject *parent = 0);
  Tool(Tool *tool, QObject *parent = 0);
  QString name() const { return _name; }
  QString section() const { return _section; }
  QString urlString() const  { return _url_string; }
  int x() const { return _x; }
  int y() const { return _y; }
signals:
  void xChanged();
  void yChanged();
public slots:
  void setX(int x);
  void setY(int y);
private:
  QString _name;
  QString _section;
  QString _url_string;
  int _x;
  int _y;
};

#endif // TOOL_H
