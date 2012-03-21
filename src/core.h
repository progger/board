/*
 * Copyright (C) 2011 Kulabuhov Michael, Kemerovo, Russia.
 *
 * See the LICENSE file for terms of use.
 */

#ifndef CORE_H
#define CORE_H

#include <QObject>

class Core : public QObject
{
  Q_OBJECT
  Q_PROPERTY(QString mode READ mode WRITE setMode NOTIFY updateMode)
  Q_PROPERTY(QString color READ color WRITE setColor NOTIFY updateColor)
  Q_PROPERTY(bool keyboard READ keyboard WRITE setKeyboard NOTIFY updateKeyboard)
  Q_PROPERTY(int fontSize READ fontSize WRITE setFontSize NOTIFY updateFontSize)

public:
  explicit Core(QObject *parent = 0);
  QString mode() const { return mode_; }
  QString color() const { return color_; }
  bool keyboard() { return keyboard_; }
  int fontSize() { return font_size_; }

signals:
  void updateMode();
  void updateColor();
  void updateKeyboard();
  void updateFontSize();

public slots:
  void setMode(const QString &mode);
  void setColor(const QString &color);
  void setKeyboard(bool keyboard);
  void setFontSize(int font_size);
  void emulateKeyPress(int key, int modifiers, const QString & text = "") const;

private:
  QString mode_;
  QString color_;
  bool keyboard_;
  int font_size_;
};

#endif // CORE_H
