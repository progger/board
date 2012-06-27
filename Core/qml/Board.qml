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
        id: menuButton
        anchors.left: parent.left
        anchors.top: parent.top
        width: style.panelSize
        height: style.panelSize
        color: style.panelColor

        Image {
            anchors.fill: parent
            anchors.margins: 3
            source: "qrc:/core/res/menu.svg"
            smooth: true
        }

        MouseArea {
            anchors.fill: parent
            onClicked: Core.menuVisible = !Core.menuVisible
        }
    }

    Menu {
        id: menu
        z: 1
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.top: menuButton.bottom
        anchors.bottom: parent.bottom
        opacity: Core.menuVisible
        Behavior on opacity {
            NumberAnimation { duration: 500 }
        }
    }

    Rectangle {
        id: toolBarRect
        anchors.left: menuButton.right
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
        anchors.top: menuButton.bottom
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
