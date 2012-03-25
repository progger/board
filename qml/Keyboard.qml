/*
 * Copyright (C) 2011 Kulabuhov Michail, Kemerovo, Russia.
 *
 * See the LICENSE file for terms of use.
 */

import QtQuick 1.1
import "keyboard.js" as Script

Rectangle {
    id: keyboard
    property variant style
    property int layout: 0
    property int shift: 0

    Column {
        anchors.fill: parent

        Repeater {
            model: Script.keys

            Row {
                x: (parent.width - width) / 2
                height: keyboard.height / 5
                spacing: 4

                Repeater {
                    model: modelData

                    Button {
                        id: button
                        style: keyboard.style
                        width: height * modelData.size
                        anchors.top: parent.top
                        anchors.topMargin: 2
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
