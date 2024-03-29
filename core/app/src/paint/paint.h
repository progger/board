/*
 * Copyright (C) 2012 Michael Kulabuhov, Kemerovo, Russia.
 *
 * See the LICENSE file for terms of use.
 */

#ifndef PAINT_H
#define PAINT_H

#include <QMap>
#include <QSharedPointer>
#include <QObject>
#include <QColor>
#include <QSize>
#include "ipaint.h"
#include "isheetcanvas.h"

class Core;
class Shape;
class ShapeGen;

class Paint final : public QObject, public IPaint
{
  Q_OBJECT
  Q_INTERFACES(IPaint)
  Q_DISABLE_COPY_MOVE(Paint)
  Q_PROPERTY(QString mode READ mode WRITE setMode NOTIFY modeChanged)
  Q_PROPERTY(float thickness READ thickness WRITE setThickness NOTIFY thicknessChanged)
  Q_PROPERTY(QColor color READ color WRITE setColor NOTIFY colorChanged)
  Q_PROPERTY(QColor bgcolor READ bgcolor WRITE setBgcolor NOTIFY bgcolorChanged)
  Q_PROPERTY(int fontSize READ fontSize WRITE setFontSize NOTIFY fontSizeChanged)
  Q_PROPERTY(float eraserSize READ eraserSize WRITE setEraserSize NOTIFY eraserSizeChanged)
  Q_PROPERTY(bool selected READ selected WRITE setSelected NOTIFY selectedChanged)
  Q_PROPERTY(bool canUndo READ canUndo WRITE setCanUndo NOTIFY canUndoChanged)
  Q_PROPERTY(bool canRedo READ canRedo WRITE setCanRedo NOTIFY canRedoChanged)
public:
  explicit Paint(Core *parent);
  ~Paint() override = default;

  // IPaint
public:
  QString mode() override;
  float thickness() override;
  QColor color() override;
  QColor bgcolor() override;
  int fontSize() override;
  float eraserSize() override;
  Shape *createShape(const QString &name, ISheetCanvas *canvas) override;
public slots:
  void RegisterShapeGen(const QString &name, ShapeGenFunc func) override;
  void RegisterShape(const QString &name, ShapeFunc func) override;
  void RegisterCursor(const QString &name, const QCursor &cursor) override;
  void setMode(const QString &mode) override;
  void setThickness(float thickness) override;
  void setColor(const QColor &color) override;
  void setBgcolor(const QColor &bgcolor) override;
  void setFontSize(int font_size) override;
  void setEraserSize(float eraser_size) override;
signals:
  void modeChanged() override;
  void thicknessChanged() override;
  void colorChanged() override;
  void bgcolorChanged() override;
  void fontSizeChanged() override;
  void eraserSizeChanged() override;

public:
  bool selected() const { return _selected; }
  bool canUndo() const { return _can_undo; }
  bool canRedo() const { return _can_redo; }
  QSize imageSize() const { return _image_size; }
  QString imageHash() const { return _image_hash; }
  QString videoSource() const { return _video_source; }
  QSharedPointer<ShapeGen> createShapeGen(ISheetCanvas *canvas) const;
  QCursor getCursor() const;
signals:
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
  void setSelected(bool selected);
  void setCanUndo(bool can_undo);
  void setCanRedo(bool can_redo);
  void selectImage(const QUrl &file_url);
  void selectVideo(const QString &url);
private:
  QString _mode;
  float _thickness;
  QColor _color;
  QColor _bgcolor;
  int _font_size;
  float _eraser_size;
  bool _selected;
  bool _can_undo;
  bool _can_redo;
  QSize _image_size;
  QString _image_hash;
  QString _video_source;
  QMap<QString, ShapeGenFunc> _map_shape_gen;
  QMap<QString, ShapeFunc> _map_shape;
  QMap<QString, QCursor> _map_cursor;
};

#endif // PAINT_H
