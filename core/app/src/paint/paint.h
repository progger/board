/*
 * Copyright (C) 2012 Michael Kulabuhov, Kemerovo, Russia.
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
#include "ipaint.h"
#include "isheetcanvas.h"

class Core;
class Shape;
class ShapeGen;

class Paint : public QObject, public IPaint
{
  Q_OBJECT
  Q_INTERFACES(IPaint)
  Q_PROPERTY(QString mode READ mode WRITE setMode NOTIFY modeChanged)
  Q_PROPERTY(float thickness READ thickness WRITE setThickness NOTIFY thicknessChanged)
  Q_PROPERTY(QColor color READ color WRITE setColor NOTIFY colorChanged)
  Q_PROPERTY(int fontSize READ fontSize WRITE setFontSize NOTIFY fontSizeChanged)
  Q_PROPERTY(bool selected READ selected WRITE setSelected NOTIFY selectedChanged)
  Q_PROPERTY(bool canUndo READ canUndo WRITE setCanUndo NOTIFY canUndoChanged)
  Q_PROPERTY(bool canRedo READ canRedo WRITE setCanRedo NOTIFY canRedoChanged)
public:
  explicit Paint(Core *parent);

  // IPaint
  virtual QString mode() override;
  virtual float thickness() override;
  virtual QColor color() override;
  virtual int fontSize() override;

  bool selected() const { return _selected; }
  bool canUndo() const { return _can_undo; }
  bool canRedo() const { return _can_redo; }
  QSize imageSize() const { return _image_size; }
  QString imageHash() const { return _image_hash; }
  QString videoSource() const { return _video_source; }
  std::shared_ptr<ShapeGen> createShapeGen(ISheetCanvas *canvas) const;
  Shape *createShape(const QString &name);
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
  void toFront();
  void toBack();
  void save();
public slots:
  // IPaint
  virtual void RegisterShapeGen(const QString &name, ShapeGenFunc func) override;
  virtual void RegisterShape(const QString &name, ShapeFunc func) override;
  virtual void setMode(const QString &mode) override;
  virtual void setThickness(float thickness) override;
  virtual void setColor(const QColor &color) override;
  virtual void setFontSize(int font_size) override;

  void setSelected(bool selected);
  void setCanUndo(bool can_undo);
  void setCanRedo(bool can_redo);
  void selectImage();
  void selectVideo();
private:
  QString _mode;
  float _thickness;
  QColor _color;
  int _font_size;
  bool _selected;
  bool _can_undo;
  bool _can_redo;
  QSize _image_size;
  QString _image_hash;
  QString _video_source;
  std::map<QString, ShapeGenFunc> _map_shape_gen;
  std::map<QString, ShapeFunc> _map_shape;
};

#endif // PAINT_H
