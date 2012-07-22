/*
 * Copyright (C) 2012 Kulabuhov Michail, Kemerovo, Russia.
 *
 * See the LICENSE file for terms of use.
 */

import QtQuick 1.1

Rectangle {
    id: board
    property Style style: Style {}

    width: 400
    height: 300

    ToolBar {
        z: 1
        id: toolBar
        width: 280
        anchors.right: parent.right
        style: board.style
        height: style.panelSize
    }

    ModeBar {
        x: parent.width - width - 20
        y: 50
        z: 2
        id: modeBar
        style: board.style
    }

    Draw {
        id: draw
        anchors.fill: parent
    }

    Keyboard {
        z: 1
        id: keyboard
        style: board.style
        anchors.bottom: parent.bottom
        anchors.horizontalCenter: parent.horizontalCenter
        height: board.height / 4
        opacity: Core.keyboard
        Behavior on opacity {
            NumberAnimation { duration: 500 }
        }
    }
}
