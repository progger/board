/*
 * Copyright (C) 2013 Michael Kulabuhov, Kemerovo, Russia.
 *
 * See the LICENSE file for terms of use.
 */

import QtQuick 2.1
import board.core.paint 2.0

TextWrapper {
    id: textWrapper
    Text {
        anchors.fill: parent
        text: textWrapper.text
        color: textWrapper.color
        font.pixelSize: textWrapper.fontSize
        transform: Scale {
            xScale: textWrapper.scalex
            yScale: textWrapper.scaley
        }
    }
}
