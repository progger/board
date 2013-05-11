/*
 * Copyright (C) 2012 Kulabuhov Michael, Kemerovo, Russia.
 *
 * See the LICENSE file for terms of use.
 */

#ifndef PAINT_H
#define PAINT_H

#include <QObject>
#include <QColor>
#include <QFile>

class Paint : public QObject
{
  Q_OBJECT
  Q_PROPERTY(QString mode READ mode WRITE setMode NOTIFY updateMode)
  Q_PROPERTY(float thickness READ thickness WRITE setThickness NOTIFY updateThickness)
  Q_PROPERTY(QColor color READ color WRITE setColor NOTIFY updateColor)
  Q_PROPERTY(int fontSize READ fontSize WRITE setFontSize NOTIFY updateFontSize)
  Q_PROPERTY(bool selected READ selected WRITE setSelected NOTIFY updateSelected)
  Q_PROPERTY(bool canUndo READ canUndo WRITE setCanUndo NOTIFY updateCanUndo)
  Q_PROPERTY(bool canRedo READ canRedo WRITE setCanRedo NOTIFY updateCanRedo)

public:
  explicit Paint(QObject *parent = 0);
  QString mode() const { return _mode; }
  float thickness() const { return _thickness; }
  QColor color() const { return _color; }
  int fontSize() const { return _font_size; }
  bool selected() const { return _selected; }
  bool canUndo() const { return _can_undo; }
  bool canRedo() const { return _can_redo; }

signals:
  void updateMode();
  void updateThickness();
  void updateColor();
  void updateFontSize();
  void updateSelected();
  void updateCanUndo();
  void updateCanRedo();
  void undo();
  void redo();
  void del();
  void duplicate();
  void save();

public slots:
  void setMode(const QString &mode);
  void setThickness(float thickness);
  void setColor(const QColor &color);
  void setFontSize(int font_size);
  void setSelected(bool selected);
  void setCanUndo(bool can_undo);
  void setCanRedo(bool can_redo);
  void selectImage();

private:
  QString _mode;
  float _thickness;
  QColor _color;
  int _font_size;
  bool _selected;
  bool _can_undo;
  bool _can_redo;

  void showFileError(const QFile &file);
};

#endif // PAINT_H
