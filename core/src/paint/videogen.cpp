/*
 * Copyright (C) 2013 Kulabuhov Michael, Kemerovo, Russia.
 *
 * See the LICENSE file for terms of use.
 */

#include "paint.h"
#include "sheetcanvas.h"
#include "videoplayer.h"
#include "videogen.h"

VideoGen::VideoGen(SheetCanvas *canvas) :
  ShapeGen(canvas)
{
  _video_source = canvas->paint()->videoSource();
}

void VideoGen::begin(const QPointF &p)
{
  QObject *obj = _canvas->paint()->compVideoPlayer()->create();
  VideoPlayer *video = qobject_cast<VideoPlayer*>(obj);
  Q_ASSERT(video);
  video->setParent(_canvas->container());
  video->setParentItem(_canvas->container());
  QSize size(_canvas->width() / 2, _canvas->width() / 8 * 3);
  video->setSize(size);
  video->setInnerSize(size);
  video->setSource(_video_source);
  _item = video;
  move(p);
}

void VideoGen::end(const QPointF &p)
{
  VideoPlayer *video = qobject_cast<VideoPlayer*>(_item);
  Q_ASSERT(video);
  emit video->play();
  ShapeGen::end(p);
  _canvas->paint()->setMode("select");
}

void VideoGen::move(const QPointF &p)
{
  _item->setPosition(QPointF(p.x() - _item->width() / 2,
                             p.y() - _item->height() / 2));
}
