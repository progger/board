/*
 * Copyright (C) 2011 Kulabuhov Michail, Kemerovo, Russia.
 *
 * See the LICENSE file for terms of use.
 */

import QtQuick 1.1

Rectangle {
    id: modeBar
    property variant style
    property int buttonSize: width - 6
    color: style.panelColor

    Column {
        y: 4
        anchors.left: parent.left
        anchors.right: parent.right
        spacing: 4

        Repeater {
            model: [
                {"mode": "pen", "image": "pen.svg"},
                {"mode": "rectangle", "image": "rectangle.svg"},
                {"mode": "circle", "image": "circle.svg"},
                {"mode": "ellipse", "image": "ellipse.svg"},
                {"mode": "text", "image": "text.svg"}
                //{"mode": "move", "image": "move.svg"}
            ]
            Button {
                style: modeBar.style
                anchors.horizontalCenter: parent.horizontalCenter
                width: buttonSize
                height: buttonSize
                image: "qrc:/res/" + modelData.image
                toggled: Core.mode == modelData.mode
                onClicked: Core.mode = modelData.mode
            }
        }
    }
}
