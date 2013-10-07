/*
 * Copyright (C) 2012 Michael Kulabuhov, Kemerovo, Russia.
 *
 * See the LICENSE file for terms of use.
 */

import QtQuick 2.1
import QtQuick.Window 2.1
import board.core 2.0

Window {
    id: board
    color: Core.transparent ? "transparent" : "white"
    Behavior on color {
        ColorAnimation { duration: 300 }
    }

    width: 400
    height: 300

    ToolBar {
        id: toolBar
        z: 1
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.top: parent.top
        height: Style.panelSize
    }

    ModeBar {
        z:2
        x: 10
        y: (parent.height - height) / 2
    }

    Item {
        id: sheetPlace
        objectName: "sheetPlace"
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.top: toolBar.bottom
        anchors.bottom: parent.bottom
    }

    Keyboard {
        id: keyboard
        z: 1
        anchors.bottom: parent.bottom
        anchors.horizontalCenter: parent.horizontalCenter
        height: board.height / 4
        opacity: Core.keyboard
        enabled: Core.keyboard
        Behavior on opacity {
            NumberAnimation { duration: 500 }
        }
    }
}
