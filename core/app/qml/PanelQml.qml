/*
 * Copyright (C) 2014 Michael Kulabuhov, Kemerovo, Russia.
 *
 * See the LICENSE file for terms of use.
 */

import QtQuick 2.0
import board.core 2.0

Rectangle {
    id: panelRect
    property variant panel
    width: panel.width * (Style.buttonSize + Style.buttonSpacing) + Style.buttonSpacing + 4
    height: panel.height * (Style.buttonSize + Style.buttonSpacing) + Style.buttonSpacing + 10
    color: panel.color
    radius: 8
    border.color: Qt.darker(color, 2)
    border.width: 2
    onXChanged: panel.x = x
    onYChanged: panel.y = y

    Component.onCompleted: {
        x = panel.x
        y = panel.y
    }

    MouseArea {
        anchors.fill: parent
        drag.target: panelRect
        drag.minimumX: 0
        drag.maximumX: board.width - width
        drag.minimumY: 0
        drag.maximumY: board.height - height
    }

    Repeater {
        model: panel.tools
        Item {
            id: toolItem
            x: modelData.x * (Style.buttonSize + Style.buttonSpacing) + Style.buttonSpacing + 2
            y: modelData.y * (Style.buttonSize + Style.buttonSpacing) + Style.buttonSpacing + 8
            width: modelData.width * (Style.buttonSize + Style.buttonSpacing) - Style.buttonSpacing
            height: modelData.height * (Style.buttonSize + Style.buttonSpacing) - Style.buttonSpacing

            Component.onCompleted: modelData.create(toolItem)
        }
    }
}
