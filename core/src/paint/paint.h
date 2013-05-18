/*
 * Copyright (C) 2012 Kulabuhov Michael, Kemerovo, Russia.
 *
 * See the LICENSE file for terms of use.
 */

#ifndef PAINT_H
#define PAINT_H

#include <memory>
#include <map>
#include <QObject>
#include <QColor>
#include <QSize>

class Core;
class SheetCanvas;
class ShapeGen;

class Paint : public QObject
{
  Q_OBJECT
  Q_PROPERTY(Core* core READ core CONSTANT)
  Q_PROPERTY(QString mode READ mode WRITE setMode NOTIFY modeChanged)
  Q_PROPERTY(float thickness READ thickness WRITE setThickness NOTIFY thicknessChanged)
  Q_PROPERTY(QColor color READ color WRITE setColor NOTIFY colorChanged)
  Q_PROPERTY(int fontSize READ fontSize WRITE setFontSize NOTIFY fontSizeChanged)
  Q_PROPERTY(bool selected READ selected WRITE setSelected NOTIFY selectedChanged)
  Q_PROPERTY(bool canUndo READ canUndo WRITE setCanUndo NOTIFY canUndoChanged)
  Q_PROPERTY(bool canRedo READ canRedo WRITE setCanRedo NOTIFY canRedoChanged)
public:
  explicit Paint(Core *parent);
  Core *core() const;
  QString mode() const { return _mode; }
  float thickness() const { return _thickness; }
  QColor color() const { return _color; }
  int fontSize() const { return _font_size; }
  bool selected() const { return _selected; }
  bool canUndo() const { return _can_undo; }
  bool canRedo() const { return _can_redo; }
  QSize imageSize() const { return _image_size; }
  QString imageSource() const { return _image_source; }
  std::shared_ptr<ShapeGen> createShapeGen(SheetCanvas *canvas) const;
signals:
  void modeChanged();
  void thicknessChanged();
  void colorChanged();
  void fontSizeChanged();
  void selectedChanged();
  void canUndoChanged();
  void canRedoChanged();
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
  QSize _image_size;
  QString _image_source;
  std::map<QString, std::shared_ptr<ShapeGen>(*)(SheetCanvas *canvas)> _map_shape_gen;
};

#endif // PAINT_H
