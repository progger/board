/*
 * Copyright (C) 2013 Michael Kulabuhov, Kemerovo, Russia.
 *
 * See the LICENSE file for terms of use.
 */

#include "global.h"
#include "paint.h"
#include "sheetcanvas.h"
#include "videoplayer.h"
#include "videogen.h"

VideoGen::VideoGen(ISheetCanvas *canvas) :
  ShapeGen(canvas)
{
  auto *canvas_obj = static_cast<SheetCanvas*>(canvas);
  _video_source = canvas_obj->paintObj()->videoSource();
}

void VideoGen::begin(const QPointF &p)
{
  auto *video = qobject_cast<VideoPlayer*>(g_core->paint()->createShape("video", _canvas));
  Q_ASSERT(video);
  QSizeF size(_canvas->viewRect().width() / 2, _canvas->viewRect().width() / 8 * 3);
  video->setSize(size);
  video->setInnerSize(size);
  video->setSource(_video_source);
  _item = video;
  move(p);
}

void VideoGen::end(const QPointF &p)
{
  auto *video = qobject_cast<VideoPlayer*>(_item);
  Q_ASSERT(video);
  emit video->play();
  ShapeGen::end(p);
  g_core->paint()->setMode("select");
}

void VideoGen::move(const QPointF &p)
{
  _item->setPosition(QPointF(p.x() - _item->width() / 2,
                             p.y() - _item->height() / 2));
}
