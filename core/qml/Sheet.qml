/*
 * Copyright (C) 2012 Kulabuhov Michail, Kemerovo, Russia.
 *
 * See the LICENSE file for terms of use.
 */

import QtQuick 2.0
import board.core.paint 1.0
import "sheet.js" as Js

Rectangle {
    anchors.fill: parent
    enabled: visible

    SheetCanvas {
        anchors.fill: parent
        core: Core
        paint: Paint

        Item {
            objectName: "container"
            anchors.fill: parent
        }

        MouseArea {
            objectName: "mouseArea"
            anchors.fill: parent
            hoverEnabled: true
            cursorShape: Js.cursors[Paint.mode]
            onPressed: parent.onMousePress(mouse)
            onReleased: parent.onMouseRelease(mouse)
            onPositionChanged: parent.onMouseMove(mouse)
        }

        Rectangle {
            id: selectRect
            objectName: "selectRect"
            z: 1
            x: 100
            y: 100
            width: 200
            height: 200
            color: "yellow"
            border.color: "black"
            border.width: 2
            opacity: 0.5
            visible: false
            property real bobberSize: 16
            property bool bobberVisible: false
            property variant selectGen

            MouseArea {
                anchors.fill: parent
                hoverEnabled: true
                cursorShape: Qt.SizeAllCursor
                onPressed: if (selectRect.selectGen)
                               selectRect.selectGen.onMoveBegin(mouse.x, mouse.y, 1, 1, 1, 1)
                onPositionChanged: if ((mouse.buttons & Qt.LeftButton) && selectRect.selectGen)
                                       selectRect.selectGen.onMove(mouse.x, mouse.y)
            }

            Repeater {
                model: [
                    [0,   0, Qt.SizeFDiagCursor],
                    [0.5, 0, Qt.SizeVerCursor],
                    [1,   0, Qt.SizeBDiagCursor],
                    [0, 0.5, Qt.SizeHorCursor],
                    [1, 0.5, Qt.SizeHorCursor],
                    [0,   1, Qt.SizeBDiagCursor],
                    [0.5, 1, Qt.SizeVerCursor],
                    [1,   1, Qt.SizeFDiagCursor]
                ]

                Rectangle {
                    z: 1
                    x: selectRect.width * modelData[0] - selectRect.bobberSize / 2
                    y: selectRect.height * modelData[1] - selectRect.bobberSize / 2
                    width: selectRect.bobberSize
                    height: selectRect.bobberSize
                    color: "aqua"
                    border.color: "black"
                    border.width: 2
                    radius: selectRect.bobberSize / 2
                    visible: selectRect.bobberVisible
                    antialiasing: true

                    MouseArea {
                        anchors.fill: parent
                        cursorShape: modelData[2]
                        onPressed: if (selectRect.selectGen)
                                       selectRect.selectGen.onScaleBegin(mouse.x, mouse.y,
                                                                         modelData[0] == 0,
                                                                         modelData[1] == 0,
                                                                         modelData[0] == 1,
                                                                         modelData[1] == 1)
                        onPositionChanged: if (selectRect.selectGen)
                                               selectRect.selectGen.onScale(mouse.x, mouse.y)
                    }
                }
            }
        }

        TextInput {
            id: textInput
            objectName: "textInput"
            property variant textItem
            visible: textItem ? true : false    // सामान्य हिंदू कोड
            x: textItem ? textItem.x : 0
            y: textItem ? textItem.y : 0
            width: contentWidth
            height: contentHeight
            font.pixelSize: textItem ? textItem.fontSize : 0
            color: textItem ? textItem.color : "black"
            transform: Scale {
                xScale: textInput.textItem ? textInput.textItem.scalex : 1
                yScale: textInput.textItem ? textInput.textItem.scaley : 1
            }

            Rectangle {
                anchors.fill: parent
                color: "transparent"
                border.color: "black"
                border.width: 2
                anchors.margins: -5
            }
        }
    }
}
