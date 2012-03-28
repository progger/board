/*
 * Copyright (C) 2011 Kulabuhov Michail, Kemerovo, Russia.
 *
 * See the LICENSE file for terms of use.
 */

import QtQuick 1.1
import "keyboard.js" as Script

Item {
    id: keyboard
    property variant style
    property int layout: 0
    property int shift: 0
    property int rowHeight: keyboard.height / Script.keys.length
    width: rowHeight * Script.getMaxLength()

    Rectangle {
        x: -8
        y: -8
        width: parent.width + 16
        height: parent.height + 12
        border.width: 8
        border.color: "#606060"
        color: "#808080"
        opacity: 0.5

        MouseArea {
            anchors.fill: parent
        }
    }

    Column {
        z: 1
        anchors.fill: parent

        Repeater {
            model: Script.keys

            Row {
                x: (parent.width - width) / 2
                height: rowHeight
                spacing: 3

                Repeater {
                    model: modelData

                    Button {
                        id: button
                        style: keyboard.style
                        width: height * modelData.size
                        anchors.top: parent.top
                        anchors.topMargin: 1
                        anchors.bottom: parent.bottom
                        anchors.bottomMargin: 2
                        text: modelData.button[keyboard.layout][keyboard.shift]
                        image: modelData.image ? "qrc:/res/" + modelData.image : ""
                        onClicked: Script.click(button, modelData)
                    }
                }
            }
        }
    }
}
