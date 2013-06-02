/*
 * Copyright (C) 2012 Kulabuhov Michael, Kemerovo, Russia.
 *
 * See the LICENSE file for terms of use.
 */

#ifndef CORE_H
#define CORE_H

#include <vector>
#include <map>
#include <QObject>
#include <QQuickView>
#include <QDir>
#include <QSettings>
#include <QQmlListProperty>
#include "quazip.h"
#include "icore.h"

class BrdStore;
class Paint;

class Core : public QObject, public ICore
{
  Q_OBJECT
  Q_INTERFACES(ICore)
  Q_PROPERTY(bool keyboard READ keyboard WRITE setKeyboard NOTIFY keyboardChanged FINAL)
  Q_PROPERTY(bool transparent READ transparent WRITE setTransparent NOTIFY transparentChanged FINAL)
  Q_PROPERTY(Paint paint READ paint CONSTANT FINAL)
  Q_PROPERTY(QQmlListProperty<QQuickItem> sheets READ sheetsProperty NOTIFY sheetsChanged FINAL)
public:
  explicit Core(QQuickView *parent = 0);
  QObject *mainView() { return parent(); }
  QDir rootDir() { return _root_dir; }
  QSettings *settings() { return _settings; }
  void showError(const QString &error);
  bool keyboard() const { return _keyboard; }
  bool transparent() const { return _transparent; }
  BrdStore *brdStore() const { return _brdStore; }
  Paint *paint() const { return _paint; }
  QQmlComponent *getComponent(const QString &urlString);
  std::vector<QQuickItem*> *sheets() { return &_sheets; }
  QQmlListProperty<QQuickItem> sheetsProperty();
signals:
  void keyboardChanged();
  void transparentChanged();
  void sheetsChanged();
public slots:
  void setKeyboard(bool keyboard);
  void setTransparent(bool transparent);
  void emulateKeyPress(int key, int modifiers, const QString & text = "") const;
  void quitButton();
  void minimizeButton();
  void saveBook();
  void saveBook(const QString &file_name);
  void openBook();
  void openBook(const QString &file_name);
private slots:
  void onMainViewStatusChanged(QQuickView::Status status);
private:
  bool _keyboard;
  bool _transparent;
  QDir _root_dir;
  QSettings *_settings;
  BrdStore *_brdStore;
  Paint *_paint;
  std::map<QString, QQmlComponent*> _map_componenet;
  QQmlComponent *_comp_sheet;
  QQuickItem *_sheet_place;
  std::vector<QQuickItem*> _sheets;
  QQuickItem *addSheet();
  void saveBookFiles(QuaZip *zip);
  void openBookFiles(QuaZip *zip);
};

#endif // CORE_H
