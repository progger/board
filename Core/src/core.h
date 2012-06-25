/*
 * Copyright (C) 2012 Kulabuhov Michael, Kemerovo, Russia.
 *
 * See the LICENSE file for terms of use.
 */

#ifndef CORE_H
#define CORE_H

#include <QObject>

class MainView;

class Core : public QObject
{
  Q_OBJECT
  Q_PROPERTY(bool keyboard READ keyboard WRITE setKeyboard NOTIFY updateKeyboard)

public:
  explicit Core(MainView *view);
  bool keyboard() { return keyboard_; }

signals:
  void updateKeyboard();

public slots:
  void setKeyboard(bool keyboard);
  void emulateKeyPress(int key, int modifiers, const QString & text = "") const;

private:
  MainView *view_;
  bool keyboard_;
};

#endif // CORE_H
