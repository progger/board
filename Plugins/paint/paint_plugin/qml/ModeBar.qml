/*
 * Copyright (C) 2012 Kulabuhov Michail, Kemerovo, Russia.
 *
 * See the LICENSE file for terms of use.
 */

import QtQuick 1.1
import "qrc:/core/qml"

Rectangle {
    id: modeBar
    property variant style: board.style
    property int buttonSize: width - 6
    width: parent.width
    color: style.panelColor

    Column {
        y: 4
        anchors.left: parent.left
        anchors.right: parent.right
        spacing: 4

        Repeater {
            model: [
                {"mode": "select", "image": "qrc:/core/res/select.svg"},
                {"mode": "pen", "image": "qrc:/plugin/res/pen.svg"},
                {"mode": "rectangle", "image": "qrc:/plugin/res/rectangle.svg"},
                {"mode": "circle", "image": "qrc:/plugin/res/circle.svg"},
                {"mode": "ellipse", "image": "qrc:/plugin/res/ellipse.svg"},
                {"mode": "text", "image": "qrc:/plugin/res/text.svg"},
                {"mode": "image", "image": "qrc:/plugin/res/image.svg"}
                //{"mode": "move", "image": "qrc:/plugin/res/move.svg"}
            ]
            Button {
                style: modeBar.style.normalButton
                anchors.horizontalCenter: parent.horizontalCenter
                width: buttonSize
                height: buttonSize
                image: modelData.image
                toggled: Paint.mode == modelData.mode
                onClicked: Paint.mode = modelData.mode
            }
        }
    }
}
