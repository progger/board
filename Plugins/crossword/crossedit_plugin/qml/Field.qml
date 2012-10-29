/*
 * Copyright (C) 2012 Kulabuhov Michail, Kemerovo, Russia.
 *
 * See the LICENSE file for terms of use.
 */

import QtQuick 1.1
import ":/lib/cross/qml"

Rectangle {
    anchors.fill: parent
    color: "white"

    CrossGrid {
        grid: Crossedit.grid
        x: parent.width * 0.05
        y: parent.height * 0.05
        width: parent.width * 0.4
        height: parent.height * 0.65
        gridColor: "#C0C0C0"
    }
}
