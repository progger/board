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

        Image {
            anchors.verticalCenter: parent.verticalCenter
            height: buttonSize
            width: buttonSize
            source: "qrc:/res/thickness.svg"
            smooth: true
        }

        SpinBox {
            style: toolBar.style
            anchors.verticalCenter: parent.verticalCenter
            width: 60
            height: buttonSize
            onValueChanged: Core.thickness = value
            step: 0.5
            minValue: 0.5
            maxValue: 10
            Component.onCompleted: value = Core.thickness
        }

        Item {
            width: 8
            height: parent.height
        }

        Image {
            anchors.verticalCenter: parent.verticalCenter
            height: buttonSize
            width: buttonSize
            source: "qrc:/res/font_size.svg"
            smooth: true
        }

        SpinBox {
            style: toolBar.style
            width: 60
            anchors.verticalCenter: parent.verticalCenter
            height: buttonSize
            onValueChanged: Core.fontSize = value
            step: 2
            minValue: 10
            maxValue: 60
            Component.onCompleted: value = Core.fontSize
        }
    }

    Button {
        x: parent.width - buttonSize - 4
        anchors.verticalCenter: parent.verticalCenter
        style: toolBar.style.closeButton
        width: buttonSize
        height: buttonSize
        image: "qrc:/res/close.svg"
        onClicked: Qt.quit()
    }
}
