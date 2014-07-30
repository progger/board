/*
 * Copyright (C) 2013 Michael Kulabuhov, Kemerovo, Russia.
 *
 * See the LICENSE file for terms of use.
 */

#ifndef VIDEOPLAYER_H
#define VIDEOPLAYER_H

#include "shape.h"

class VideoPlayer : public Shape
{
  Q_OBJECT
  Q_PROPERTY(QString source READ source WRITE setSource NOTIFY sourceChanged)
public:
  explicit VideoPlayer(QQuickItem *parent = 0);
  QString source() const { return _source; }
public slots:
  void setSource(const QString &source);
signals:
  void sourceChanged();
  void play();
protected:
  virtual QString elementName() const override;
  virtual void innerSerialize(QXmlStreamWriter *writer, QSet<QString> *brd_objects) const override;
  virtual void innerDeserialize(QXmlStreamReader *reader) override;
private:
  QString _source;
};

#endif // VIDEOPLAYER_H
