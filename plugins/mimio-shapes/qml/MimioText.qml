/*
 * Copyright (C) 2013 Michael Kulabuhov, Kemerovo, Russia.
 *
 * See the LICENSE file for terms of use.
 */

import QtQuick 2.1
import board.mimio 2.0

MimioText {
    id: mimioText
    Text {
        anchors.fill: parent
        text: mimioText.text
        textFormat: Text.RichText
        wrapMode: Text.WordWrap
        transform: Scale {
            xScale: mimioText.scalex
            yScale: mimioText.scaley
        }
    }
}
