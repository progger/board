/*
 * Copyright (C) 2013 Kulabuhov Michael, Kemerovo, Russia.
 *
 * See the LICENSE file for terms of use.
 */

#ifndef TEXTWRAPPER_H
#define TEXTWRAPPER_H

#include "shape.h"

class TextWrapper : public Shape
{
  Q_OBJECT
  Q_PROPERTY(QString text READ text WRITE setText NOTIFY textChanged)
  Q_PROPERTY(int fontSize READ fontSize WRITE setFontSize NOTIFY fontSizeChanged)
  Q_PROPERTY(QObject* textElement READ textElement CONSTANT)
public:
  explicit TextWrapper(QQuickItem *parent = 0);
  QString text() const { return _text; }
  int fontSize() const { return _font_size; }
  QObject *textElement() const;
public slots:
  void setText(const QString &text);
  void setFontSize(int font_size);
signals:
  void textChanged();
  void fontSizeChanged();
private:
  QString _text;
  int _font_size;
};

#endif // TEXTWRAPPER_H
