/*
 * Copyright (C) 2012 Michael Kulabuhov, Kemerovo, Russia.
 *
 * See the LICENSE file for terms of use.
 */

import QtQuick 2.0

Rectangle {
    id: board
    property Style style: Style {}
    color: Core.transparent ? "transparent" : "white"
    Behavior on color {
        ColorAnimation { duration: 300 }
    }

    focus: true

    width: 400
    height: 300

    ToolBar {
        id: toolBar
        z: 1
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.top: parent.top
        height: board.style.panelSize
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
        style: board.style
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
