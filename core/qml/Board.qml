/*
 * Copyright (C) 2012 Kulabuhov Michail, Kemerovo, Russia.
 *
 * See the LICENSE file for terms of use.
 */

import QtQuick 2.0
import board.core.paint 1.0

Rectangle {
    id: board
    property variant sheetComponent: Qt.createComponent("Sheet.qml")
    property Style style: Style {}
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

    Rectangle {
        id: sheetPlace
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

    Component.onCompleted: if (sheetComponent.status == Component.Error) console.log(sheetComponent.errorString())
}
