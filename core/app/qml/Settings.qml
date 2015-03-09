/*
 * Copyright (C) 2015 Michael Kulabuhov, Kemerovo, Russia.
 *
 * See the LICENSE file for terms of use.
 */

import QtQuick 2.0
import QtQuick.Controls 1.3
import QtQuick.Dialogs 1.0
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
                        onClicked: colorDialog.open()
                    }

                    ColorDialog {
                        id: colorDialog
                        color: colorRect.color
                        onAccepted: {
                            Core.sheets[Core.sheetIndex].color = color
                            colorRect.color = color
                        }
                    }
                }
            }

            Button {
                width: 200
                height: 28
                style: Style.normalButton
                text: "Применить ко всем"
                onClicked: {
                    var cur = Core.sheets[Core.sheetIndex]
                    for (var i in Core.sheets)
                    {
                        var sheet = Core.sheets[i]
                        sheet.copySettings(cur)
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
