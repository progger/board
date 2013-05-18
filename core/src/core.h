/*
 * Copyright (C) 2012 Kulabuhov Michael, Kemerovo, Russia.
 *
 * See the LICENSE file for terms of use.
 */

#ifndef CORE_H
#define CORE_H

#include <map>
#include <QObject>
#include <QQuickView>
#include <QDir>
#include <QSettings>
#include "icore.h"

class BrdStore;
class Paint;

class Core : public QObject, public ICore
{
  Q_OBJECT
  Q_INTERFACES(ICore)
  Q_PROPERTY(bool keyboard READ keyboard WRITE setKeyboard NOTIFY updateKeyboard FINAL)
  Q_PROPERTY(Paint paint READ paint CONSTANT FINAL)
public:
  explicit Core(QQuickView *parent = 0);
  QObject *mainView() { return parent(); }
  QDir rootDir() { return _root_dir; }
  QSettings *settings() { return _settings; }
  void showError(const QString &error);
  bool keyboard() const { return _keyboard; }
  BrdStore *brdStore() const { return _brdStore; }
  Paint *paint() const { return _paint; }
  QQmlComponent *getComponent(const QString &urlString);
signals:
  void updateKeyboard();
public slots:
  void setKeyboard(bool keyboard);
  void emulateKeyPress(int key, int modifiers, const QString & text = "") const;
  void quitButton();
  void minimizeButton();
private:
  bool _keyboard;
  QDir _root_dir;
  QSettings *_settings;
  BrdStore *_brdStore;
  Paint *_paint;
  std::map<QString, QQmlComponent*> _map_componenet;
};

#endif // CORE_H
