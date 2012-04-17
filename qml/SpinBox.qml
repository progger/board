/*
 * Copyright (C) 2012 Kulabuhov Michail, Kemerovo, Russia.
 *
 * See the LICENSE file for terms of use.
 */

import QtQuick 1.1

Rectangle {
    id: spinBox
    property variant style
    property real value: 0
    property real step: 1
    property real minValue: 0
    property real maxValue: 100
    border.width: 2
    border.color: "black"
    color: "white"
    radius: 4

    Item {
        anchors.top: parent.top
        anchors.bottom: parent.bottom
        anchors.left: parent.left
        anchors.right: buttons.left

        Text {
            anchors.centerIn: parent
            font.pixelSize: parent.height / 2
            text: value.toPrecision(2);
            smooth: true
        }
    }

    Item {
        id: buttons
        anchors.top: parent.top
        anchors.bottom: parent.bottom
        anchors.right: parent.right
        width: parent.height / 2

        Button {
            style: spinBox.style.normalButton
            anchors.right: parent.right
            anchors.top: parent.top
            anchors.bottom: parent.verticalCenter
            width: height
            radius: 4
            image: "qrc:/res/up_arrow.svg"
            onClicked: value = Math.min(value + step, maxValue)
        }

        Button {
            style: spinBox.style.normalButton
            anchors.right: parent.right
            anchors.top: parent.verticalCenter
            anchors.bottom: parent.bottom
            width: height
            radius: 4
            image: "qrc:/res/down_arrow.svg"
            onClicked: value = Math.max(value - step, minValue)
        }
    }
}
