/*
 * Copyright (C) 2012 Kulabuhov Michail, Kemerovo, Russia.
 *
 * See the LICENSE file for terms of use.
 */

import QtQuick 2.0

Rectangle {
    id: menu
    property list<QtObject> items
    width: menuColumn.width + menuColumn.x * 2
    height: menuColumn.height + menuColumn.y * 2
    color: "white"
    border.width: 2
    border.color: "black"
    enabled: false
    opacity: enabled
    Behavior on opacity {
        NumberAnimation { duration: 300 }
    }

    MouseArea {
        anchors.fill: parent
        hoverEnabled: true
        onExited: menu.enabled = false

        Column {
            id: menuColumn
            x: 4
            y: 4

            Repeater {
                model: items

                Item {
                    width: menuItemText.width
                    height: 25

                    Rectangle {
                        width: menuColumn.width
                        height: parent.height
                        color: menuItemMouseArea.containsMouse ? "aqua" : "white"

                        Text {
                            id: menuItemText
                            height: parent.height
                            font.pixelSize: height * 0.7
                            text: modelData.name
                        }

                        MouseArea {
                            id: menuItemMouseArea
                            anchors.fill: parent
                            hoverEnabled: true
                            onClicked: modelData.onClicked()
                        }
                    }
                }
            }
        }
    }
}
