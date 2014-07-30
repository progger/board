/*
 * Copyright (C) 2014 Michael Kulabuhov, Kemerovo, Russia.
 *
 * See the LICENSE file for terms of use.
 */

#ifndef MPXEVENTFILTER_H
#define MPXEVENTFILTER_H

#include <map>
#include <QAbstractNativeEventFilter>
#include <QWindow>

class MpxEventFilter : public QAbstractNativeEventFilter
{
public:
  MpxEventFilter(QWindow *window);
  virtual bool nativeEventFilter(const QByteArray &eventType, void *message, long *) override;
private:
  QWindow *_window;
  std::map<quint16, Qt::MouseButtons> _buttons;
};

#endif // MPXEVENTFILTER_H
