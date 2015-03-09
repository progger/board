/*
 * Copyright (C) 2015 Michael Kulabuhov, Kemerovo, Russia.
 *
 * See the LICENSE file for terms of use.
 */

import QtQuick 2.0
import QtQuick.Controls 1.3
import board.core 2.0

Rectangle {
    color: "white"

    Item {
        id: sheetSettings
        anchors.left: parent.left
        anchors.top: parent.top
        anchors.bottom: parent.bottom
        width: parent.width / 2

        Column {
            anchors.fill: parent
            anchors.margins: 8
            spacing: 8

            CheckBox {
                id: chbScrollable
                text: "Неограниченный лист"
                onCheckedChanged: Core.sheets[Core.sheetIndex].scrollable = checked
            }

            Row {
                spacing: 8

                Label {
                    id: colorLabel
                    text: "Цвет:"
                }

                Rectangle {
                    id: colorRect
                    width: 50
                    height: colorLabel.height
                    border.color: "black"

                    MouseArea {
                        anchors.fill: parent
                        onClicked: colorGridRect.opacity = !colorGridRect.opacity
                    }

                    ColorGrid {
                        id: colorGridRect
                        x: 0
                        y: parent.height
                        cellSize: Style.buttonSize
                        onSelect: {
                            Core.sheets[Core.sheetIndex].color = color
                            colorRect.color = color
                        }
                    }
                }
            }
        }
    }

    Connections {
        target: Core
        onSheetIndexChanged: {
            var sheet = Core.sheets[Core.sheetIndex]
            chbScrollable.checked = sheet.scrollable
            colorRect.color = sheet.color
        }
    }

    MouseArea {
        z: -1
        anchors.fill: parent
    }
}
