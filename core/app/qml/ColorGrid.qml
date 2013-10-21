/*
 * Copyright (C) 2013 Michael Kulabuhov, Kemerovo, Russia.
 *
 * See the LICENSE file for terms of use.
 */

import QtQuick 2.1

Rectangle {
    id: colorGridRect
    property real cellSize
    signal select (color color)
    border.color: "#404040"
    border.width: 2
    width: colorGrid.width + 4
    height: colorGrid.height + 4
    color: "#E0E0E0"
    opacity: 0
    enabled: opacity
    Behavior on opacity {
        NumberAnimation { duration: 500 }
    }

    GridView {
        id: colorGrid
        x: 4
        y: 4
        cellWidth: cellSize + 4
        cellHeight: cellSize + 4
        model: [
            "#000000", "#ff0000", "#00ff00", "#0000ff",
            "#ffff00", "#ff00ff", "#00ffff", "#800000",
            "#008000", "#000080", "#808000", "#800080",
            "#008080", "#808080", "#00000000"
        ]
        width: cellWidth * 4
        height: cellHeight * 4
        delegate: colorGridDelegate

        Component {
            id: colorGridDelegate
            Rectangle {
                height: cellSize
                width: cellSize
                color: modelData

                MouseArea {
                    anchors.fill: parent
                    onClicked: {
                        select(modelData)
                        colorGridRect.opacity = 0
                    }
                }
            }
        }
    }
}
