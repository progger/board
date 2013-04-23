/*
 * Copyright (C) 2012 Kulabuhov Michail, Kemerovo, Russia.
 *
 * See the LICENSE file for terms of use.
 */

import QtQuick 2.0
import "sheet.js" as Script

Item {
    anchors.fill: parent

    Canvas {
        id: canvas
        anchors.fill: parent
        contextType: "2d"
        onPaint: Script.paint(region)
    }

    MouseArea {
        anchors.fill: parent
        hoverEnabled: true
        onPressed: Script.mouseDown(mouse)
        onReleased: Script.mouseUp(mouse)
        onPositionChanged: Script.mouseMove(mouse)
        cursorShape: Qt.CrossCursor
    }

    Component.onCompleted: Script.init()
}
