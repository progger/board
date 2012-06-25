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

    Rectangle {
        id: toolBarRect
        anchors.left: menu.right
        anchors.right: parent.right
        height: style.panelSize
        color: style.panelColor

        Button {
            property int buttonSize: parent.height - 6
            x: parent.width - buttonSize - 4
            anchors.verticalCenter: parent.verticalCenter
            style: board.style.closeButton
            width: buttonSize
            height: buttonSize
            image: "qrc:/core/res/close.svg"
            onClicked: Qt.quit()
        }
    }

    Rectangle {
        id: modeBarRect
        anchors.top: menu.bottom
        anchors.bottom: parent.bottom
        anchors.left: parent.left
        width: style.panelSize
        color: style.panelColor
    }

    Draw {
        anchors.top: toolBarRect.bottom
        anchors.bottom: parent.bottom
        anchors.left: modeBarRect.right
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
