/*
 * Copyright (C) 2011 Kulabuhov Michail, Kemerovo, Russia.
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

    Rectangle {
        id: centerArea
        anchors.top: menu.bottom
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.bottom: parent.bottom

        ModeBar {
            id: modeBar
            anchors.top: parent.top
            anchors.bottom: parent.bottom
            anchors.left: parent.left
            width: 44
            style: board.style
        }

        Draw {
            anchors.top: parent.top
            anchors.bottom: parent.bottom
            anchors.left: modeBar.right
            anchors.right: parent.right
        }
    }

    Keyboard {
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
