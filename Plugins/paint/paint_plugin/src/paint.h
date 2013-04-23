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
  Q_PROPERTY(int imageWidth READ imageWidth WRITE setImageWidth NOTIFY updateImageWidth)
  Q_PROPERTY(int imageHeight READ imageHeight WRITE setImageHeight NOTIFY updateImageHeight)
  Q_PROPERTY(QString imageContent READ imageContent WRITE setImageContent NOTIFY updateImageContent)
  Q_PROPERTY(bool canUndo READ canUndo WRITE setCanUndo NOTIFY updateCanUndo)
  Q_PROPERTY(bool canRedo READ canRedo WRITE setCanRedo NOTIFY updateCanRedo)

public:
  explicit Paint(QObject *parent = 0);
  QString mode() const { return mode_; }
  float thickness() { return thickness_; }
  QColor color() const { return color_; }
  Q_INVOKABLE QColor getColor() const { return color_; }
  int fontSize() const { return font_size_; }
  bool selected() const { return selected_; }
  int imageWidth() const { return image_width_; }
  int imageHeight() const { return image_height_; }
  QString imageContent() const { return image_content_; }
  bool canUndo() const { return can_undo_; }
  bool canRedo() const { return can_redo_; }
  Q_INVOKABLE QColor selectColor(QColor color);

signals:
  void updateMode();
  void updateThickness();
  void updateColor();
  void updateFontSize();
  void updateSelected();
  void updateImageWidth();
  void updateImageHeight();
  void updateImageContent();
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
  void setImageWidth(int width);
  void setImageHeight(int height);
  void setImageContent(const QString &imageContent);
  void setCanUndo(bool can_undo);
  void setCanRedo(bool can_redo);
  void saveContent(const QString &content);
  void selectImage();

private:
  QString mode_;
  float thickness_;
  QColor color_;
  int font_size_;
  bool selected_;
  int image_width_;
  int image_height_;
  QString image_content_;
  bool can_undo_;
  bool can_redo_;

  void showFileError(const QFile &file);
};

#endif // PAINT_H
