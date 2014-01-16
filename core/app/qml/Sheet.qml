/*
 * Copyright (C) 2013 Michael Kulabuhov, Kemerovo, Russia.
 *
 * See the LICENSE file for terms of use.
 */

import QtQuick 2.1
import board.core.paint 2.0
import "sheet.js" as Js

Sheet {
    anchors.fill: parent
    enabled: visible

    SheetCanvas {
        id: sheetCanvas
        objectName: "sheetCanvas"
        anchors.left: parent.left
        anchors.top: parent.top
        anchors.right: vscroll.left
        anchors.bottom: hscroll.top
        clip: true

        Item {
            id: container
            objectName: "container"
            anchors.fill: parent
        }

        MouseArea {
            id: mouseArea
            z: -1
            objectName: "mouseArea"
            anchors.fill: parent
            hoverEnabled: true
            cursorShape: Js.cursors[Paint.mode]
            acceptedButtons: Qt.NoButton
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
                cursorShape: parent.bobberVisible ? Qt.SizeAllCursor : Qt.ArrowCursor
                onPressed: if (selectRect.selectGen)
                               selectRect.selectGen.onMoveBegin(mouse.x, mouse.y, 1, 1, 1, 1)
                onReleased: if (selectRect.selectGen)
                                selectRect.selectGen.onMoveEnd()
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
                        onReleased: if (selectRect.selectGen)
                                        selectRect.selectGen.onScaleEnd()
                        onPositionChanged: if (selectRect.selectGen)
                                               selectRect.selectGen.onScale(mouse.x, mouse.y)
                    }
                }
            }
        }

        TextEdit {
            id: textInput
            objectName: "textInput"
            property variant textGen
            property variant textItem
            x: textItem ? textItem.x : 0
            y: textItem ? textItem.y : 0
            visible: false
            width: contentWidth
            height: contentHeight
            transform: Scale {
                id: textInputScale
            }

            onTextItemChanged: updateTextInput()
            function updateTextInput()
            {
                if (textItem)
                {
                    visible = true;
                    font.family = textItem.fontFamily;
                    font.pixelSize = textItem.fontSize;
                    color = textItem.color;
                    textInputScale.xScale = textItem.scalex;
                    textInputScale.yScale = textItem.scaley;
                    text = textItem.text;
                    cursorPosition = positionAt((mouseArea.mouseX - textItem.x) / textItem.scalex,
                                                (mouseArea.mouseY - textItem.y) / textItem.scaley);
                    Core.keyboard = true;
                }
                else
                {
                    visible = false;
                    Core.keyboard = false;
                }
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

    ScrollBar {
        id: vscroll
        property rect sheetRect: sheetCanvas.sheetRect
        horizontal: false
        anchors.top: parent.top
        anchors.right: parent.right
        anchors.bottom: hscroll.top
        width: 20
        onLeftButton: sheetCanvas.moveSheet(0, -10)
        onRightButton: sheetCanvas.moveSheet(0, 10)
        onLeftPage: sheetCanvas.moveSheet(0, -sheetCanvas.height / 2)
        onRightPage: sheetCanvas.moveSheet(0, sheetCanvas.height / 2)
        onSheetRectChanged: updateScroll()
        onMove: sheetCanvas.moveSheet(0, sheetCanvas.height * step)

        function updateScroll() {
            position = -sheetCanvas.sheetRect.y / sheetCanvas.sheetRect.height;
            length = sheetCanvas.height / sheetCanvas.sheetRect.height;
        }
    }

    ScrollBar {
        id: hscroll
        property rect sheetRect: sheetCanvas.sheetRect
        horizontal: true
        anchors.left: parent.left
        anchors.right: vscroll.left
        anchors.bottom: parent.bottom
        height: 20
        onLeftButton: sheetCanvas.moveSheet(-10, 0)
        onRightButton: sheetCanvas.moveSheet(10, 0)
        onLeftPage: sheetCanvas.moveSheet(-sheetCanvas.width / 2, 0)
        onRightPage: sheetCanvas.moveSheet(sheetCanvas.width / 2, 0)
        onSheetRectChanged: updateScroll()
        onMove: sheetCanvas.moveSheet(sheetCanvas.width * step, 0)

        function updateScroll() {
            position = -sheetCanvas.sheetRect.x / sheetCanvas.sheetRect.width;
            length = sheetCanvas.width / sheetCanvas.sheetRect.width;
        }
    }
}
