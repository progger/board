/*
 * Copyright (C) 2013 Michael Kulabuhov, Kemerovo, Russia.
 *
 * See the LICENSE file for terms of use.
 */

import QtQuick 2.0
import board.core.paint 2.0

ImageWrapper {
    id: imageWrapper
    Image {
        anchors.fill: parent
        source: imageWrapper.source
    }
}
