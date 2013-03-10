/*
 * Copyright (C) 2012 Kulabuhov Michail, Kemerovo, Russia.
 *
 * See the LICENSE file for terms of use.
 */

import QtQuick 2.0
import "qrc:/core/qml"

Rectangle {
    id: toolBar
    property variant style: board.style
    property int buttonSize: height - 6
    anchors.top: parent.top
    anchors.right: parent.Left
    width: 280
    height: style.panelSize
    color: style.panelColor

    Row {
        anchors.top: parent.top
        anchors.bottom: parent.bottom
        spacing: 4

        Image {
            anchors.verticalCenter: parent.verticalCenter
            height: buttonSize
            width: buttonSize
            source: "qrc:/plugin/paint/res/thickness.svg"
            smooth: true
        }

        SpinBox {
            style: toolBar.style
            anchors.verticalCenter: parent.verticalCenter
            width: 60
            height: buttonSize
            onValueChanged: Paint.thickness = value
            step: 0.5
            minValue: 0.5
            maxValue: 10
            Component.onCompleted: value = Paint.thickness
        }

        Item {
            width: 8
            height: parent.height
        }

        Image {
            anchors.verticalCenter: parent.verticalCenter
            height: buttonSize
            width: buttonSize
            source: "qrc:/plugin/paint/res/font_size.svg"
            smooth: true
        }

        SpinBox {
            style: toolBar.style
            width: 60
            anchors.verticalCenter: parent.verticalCenter
            height: buttonSize
            onValueChanged: Paint.fontSize = value
            step: 2
            minValue: 10
            maxValue: 60
            Component.onCompleted: value = Paint.fontSize
        }
    }
}
