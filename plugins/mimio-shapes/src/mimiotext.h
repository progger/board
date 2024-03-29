/*
 * Copyright (C) 2015 Michael Kulabuhov, Kemerovo, Russia.
 *
 * See the LICENSE file for terms of use.
 */

#ifndef MIMIOTEXT_H
#define MIMIOTEXT_H

#include "shape.h"

class MimioText : public Shape
{
  Q_OBJECT
  Q_DISABLE_COPY_MOVE(MimioText)
  Q_PROPERTY(QString text READ text WRITE setText NOTIFY textChanged)
public:
  explicit MimioText(QQuickItem *parent = nullptr);
  ~MimioText() override = default;
  QString text() const;
public slots:
  void setHash(const QString &hash);
  void setText(const QString &text);
signals:
  void textChanged();
protected:
  QString elementName() const override;
  void innerSerialize(QXmlStreamWriter *writer, QSet<QString> *brd_objects) const override;
  void innerDeserialize(QXmlStreamReader *reader) override;
private:
  QString _hash;
};

#endif // MIMIOTEXT_H
