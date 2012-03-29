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

    Rectangle {
        id: menu
        anchors.left: parent.left
        anchors.top: parent.top
        width: style.panelSize
        height: style.panelSize
        color: style.panelColor
    }

    ToolBar {
        z: 1
        id: toolBar
        anchors.left: menu.right
        anchors.right: parent.right
        style: board.style
        height: style.panelSize
    }

    ModeBar {
        id: modeBar
        anchors.top: menu.bottom
        anchors.bottom: parent.bottom
        anchors.left: parent.left
        width: 44
        style: board.style
    }

    Draw {
        anchors.top: toolBar.bottom
        anchors.bottom: parent.bottom
        anchors.left: modeBar.right
        anchors.right: parent.right
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
