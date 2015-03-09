/*
 * Copyright (C) 2015 Michael Kulabuhov, Kemerovo, Russia.
 *
 * See the LICENSE file for terms of use.
 */

import QtQuick 2.0
import QtQuick.Controls 1.3
import QtQuick.Layouts 1.1
import board.core 2.0

Rectangle {
    color: "white"

    Item {
        id: sheetSettings
        anchors.left: parent.left
        anchors.top: parent.top
        anchors.bottom: parent.bottom
        width: parent.width / 2

        ColumnLayout {
            spacing: 8

            CheckBox {
                id: chbScrollable
                text: "Неограниченный лист"
                onCheckedChanged: Core.sheets[Core.sheetIndex].scrollable = checked
            }
        }
    }

    Connections {
        target: Core
        onSheetIndexChanged: {
            var sheet = Core.sheets[Core.sheetIndex]
            chbScrollable.checked = sheet.scrollable
        }
    }

    MouseArea {
        z: -1
        anchors.fill: parent
    }
}
