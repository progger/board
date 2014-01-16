#include <QGuiApplication>
#include <QMouseEvent>
#include <xcb/xcb.h>
#include <xcb/xinput.h>
#include "mpxeventfilter.h"

MpxEventFilter::MpxEventFilter(QWindow *window) :
  QAbstractNativeEventFilter(),
  _window(window),
  _buttons()
{
}

bool MpxEventFilter::nativeEventFilter(const QByteArray &eventType, void *message, long *)
{
  if (eventType == "xcb_generic_event_t") {
      xcb_generic_event_t* ev = static_cast<xcb_generic_event_t *>(message);
      if (ev->response_type == 35)
      {
        xcb_input_button_press_event_t *pointer = static_cast<xcb_input_button_press_event_t*>(message);
        quint16 id = pointer->deviceid;
        QPointF pos = QPointF(pointer->event_x >> 16, pointer->event_y >> 16);
        Qt::MouseButton btn = Qt::NoButton;
        Qt::MouseButtons btns = _buttons[id];
        Qt::KeyboardModifier mod = Qt::KeyboardModifier(id);
        QMouseEvent *event = nullptr;

        switch (pointer->detail) {
        case 1:
          btn = Qt::LeftButton;
          break;
        case 2:
          btn = Qt::MidButton;
        case 3:
          btn = Qt::RightButton;
          break;
        }

        switch (pointer->event_type) {
        case XCB_INPUT_BUTTON_PRESS:
          btns |= btn;
          _buttons[id] = btns;
          event = new QMouseEvent(QEvent::MouseButtonPress, pos, btn, btns, mod);
          break;
        case XCB_INPUT_BUTTON_RELEASE:
          btns &= !btn;
          _buttons[id] = btns;
          event = new QMouseEvent(QEvent::MouseButtonRelease, pos, btn, btns, mod);
          break;
        case XCB_INPUT_MOTION:
          event = new QMouseEvent(QEvent::MouseMove, pos, btn, btns, mod);
          break;
        }

        if (event)
        {
          QGuiApplication::postEvent(_window, event);
          return true;
        }
      }
  }
  return false;
}
