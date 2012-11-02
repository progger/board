/*
 * Copyright (C) 2012 Kulabuhov Michail, Kemerovo, Russia.
 *
 * See the LICENSE file for terms of use.
 */

import QtQuick 1.1

Item {
    property variant grid
    property real cellSize: Math.min(width / grid.width, height / grid.height)
    property color gridColor: "transparent"
    signal cellClicked(variant cell)

    Column {
        x: (parent.width - width) / 2
        y: (parent.height - height) / 2

        Repeater {
            model: grid.rows

            Row {

                Repeater {
                    model: modelData.cells

                    Rectangle {
                        width: cellSize
                        height: cellSize
                        color: getCellColor(modelData)
                        border.width: 1
                        border.color: modelData.type ? "black" : gridColor

                        Text {
                            color: "black"
                            anchors.centerIn: parent
                            font.pixelSize: parent.height / 2
                            text: modelData.letter
                            smooth: true
                        }

                        MouseArea {
                            anchors.fill: parent
                            onClicked: cellClicked(modelData)
                        }

                        function getCellColor(cell) {
                            switch (cell.type)
                            {
                            case 0:
                                return "transparent";
                            case 1:
                                return "black";
                            case 2:
                                return cell.accepted
                                        ? "#C0FFC0"
                                        : cell.editing
                                          ? "#FFA0A0"
                                          : cell.highlight
                                            ? "#A0A0FF"
                                            : cell.error
                                              ? "#FF8080"
                                              : "white";
                            }
                        }
                    }
                }
            }
        }
    }
}
