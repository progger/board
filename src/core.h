/*
 * Copyright (C) 2012 Kulabuhov Michael, Kemerovo, Russia.
 *
 * See the LICENSE file for terms of use.
 */

#ifndef CORE_H
#define CORE_H

#include <QObject>
#include <QColor>

class MainView;

class Core : public QObject
{
  Q_OBJECT
  Q_PROPERTY(QString mode READ mode WRITE setMode NOTIFY updateMode)
  Q_PROPERTY(QString color READ color WRITE setColor NOTIFY updateColor)
  Q_PROPERTY(bool keyboard READ keyboard WRITE setKeyboard NOTIFY updateKeyboard)
  Q_PROPERTY(int fontSize READ fontSize WRITE setFontSize NOTIFY updateFontSize)
  Q_PROPERTY(bool selected READ selected WRITE setSelected NOTIFY updateSelected)

public:
  explicit Core(MainView *view);
  QString mode() const { return mode_; }
  QString color() const { return color_; }
  bool keyboard() { return keyboard_; }
  int fontSize() { return font_size_; }
  bool selected() { return selected_; }
  Q_INVOKABLE QColor selectColor(QColor color);

signals:
  void updateMode();
  void updateColor();
  void updateKeyboard();
  void updateFontSize();
  void updateSelected();
  void undo();
  void redo();
  void del();
  void duplicate();
  void save();

public slots:
  void setMode(const QString &mode);
  void setColor(const QString &color);
  void setKeyboard(bool keyboard);
  void setFontSize(int font_size);
  void setSelected(bool selected);
  void emulateKeyPress(int key, int modifiers, const QString & text = "") const;
  void saveContent(const QString &content);

private:
  MainView *view_;
  QString mode_;
  QString color_;
  bool keyboard_;
  int font_size_;
  bool selected_;
};

#endif // CORE_H
