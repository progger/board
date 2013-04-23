/*
 * Copyright (C) 2012 Kulabuhov Michail, Kemerovo, Russia.
 *
 * See the LICENSE file for terms of use.
 */

import QtQuick 2.0
import "board.js" as Script

Rectangle {
    id: board
    property Style style: Style {}
    focus: true

    width: 400
    height: 300

    Button {
        id: closeButton
        z: 11
        style: board.style.closeButton
        anchors.right: parent.right
        anchors.top: parent.top
        width: board.style.panelSize
        height: board.style.panelSize
        image: "qrc:/core/res/close.svg"
        onClicked: Core.quitButton();
    }

    Button {
        id: minimizeButton
        z: 11
        style: board.style.minimizeButton
        x: closeButton.x - width - 4
        anchors.top: parent.top
        width: board.style.panelSize
        height: board.style.panelSize
        image: "qrc:/core/res/minimize.svg"
        onClicked: Core.minimizeButton();
    }

    Menu {
        id: menu
        z: 10
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.top: parent.top
        anchors.bottom: parent.bottom
        opacity: Core.menuVisible
        enabled: Core.menuVisible
        Behavior on opacity {
            NumberAnimation { duration: 300 }
        }
    }

    Keyboard {
        id: keyboard
        z: 5
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
