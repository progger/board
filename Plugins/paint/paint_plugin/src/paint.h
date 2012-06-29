/*
 * Copyright (C) 2012 Kulabuhov Michael, Kemerovo, Russia.
 *
 * See the LICENSE file for terms of use.
 */

#ifndef PAINT_H
#define PAINT_H

#include <QWidget>
#include <QObject>
#include <QColor>
#include <QFile>

class Paint : public QObject
{
  Q_OBJECT
  Q_PROPERTY(QString mode READ mode WRITE setMode NOTIFY updateMode)
  Q_PROPERTY(float thickness READ thickness WRITE setThickness NOTIFY updateThickness)
  Q_PROPERTY(QString color READ color WRITE setColor NOTIFY updateColor)
  Q_PROPERTY(int fontSize READ fontSize WRITE setFontSize NOTIFY updateFontSize)
  Q_PROPERTY(bool selected READ selected WRITE setSelected NOTIFY updateSelected)
  Q_PROPERTY(int imageWidth READ imageWidth WRITE setImageWidth NOTIFY updateImageWidth)
  Q_PROPERTY(int imageHeight READ imageHeight WRITE setImageHeight NOTIFY updateImageHeight)
  Q_PROPERTY(QString imageContent READ imageContent WRITE setImageContent NOTIFY updateImageContent)
  Q_PROPERTY(bool canUndo READ canUndo WRITE setCanUndo NOTIFY updateCanUndo)
  Q_PROPERTY(bool canRedo READ canRedo WRITE setCanRedo NOTIFY updateCanRedo)

public:
  explicit Paint(QWidget *view, QObject *parent = 0);
  QString mode() const { return mode_; }
  float thickness() { return thickness_; }
  QString color() const { return color_; }
  int fontSize() { return font_size_; }
  bool selected() { return selected_; }
  int imageWidth() { return image_width_; }
  int imageHeight() { return image_height_; }
  QString imageContent() { return image_content_; }
  bool canUndo() { return can_undo_; }
  bool canRedo() { return can_redo_; }
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
  void setColor(const QString &color);
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
  QWidget *view_;
  QString mode_;
  float thickness_;
  QString color_;
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
