/*
 * Copyright (C) 2012 Kulabuhov Michail, Kemerovo, Russia.
 *
 * See the LICENSE file for terms of use.
 */

import QtQuick 1.1

Rectangle {
    id: toolBar
    property variant style
    property int buttonSize: height - 6
    color: style.panelColor

    Row {
        anchors.top: parent.top
        anchors.bottom: parent.bottom
        spacing: 4

        ColorSelector {
            style: toolBar.style
            anchors.verticalCenter: parent.verticalCenter
            height: parent.height
        }

        Item {
            width: 16
            height: parent.height
        }

        Button {
            anchors.verticalCenter: parent.verticalCenter
            style: toolBar.style
            width: buttonSize
            height: buttonSize
            image: "qrc:/res/undo.svg"
            onClicked: Core.undo()
        }

        Button {
            anchors.verticalCenter: parent.verticalCenter
            style: toolBar.style
            width: buttonSize
            height: buttonSize
            image: "qrc:/res/redo.svg"
            onClicked: Core.redo()
        }
    }

    Button {
        x: parent.width - buttonSize - 4
        anchors.verticalCenter: parent.verticalCenter
        style: toolBar.style
        width: buttonSize
        height: buttonSize
        image: "qrc:/res/close.svg"
        onClicked: Qt.quit()
    }
}
