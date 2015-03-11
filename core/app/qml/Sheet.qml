/*
 * Copyright (C) 2013 Michael Kulabuhov, Kemerovo, Russia.
 *
 * See the LICENSE file for terms of use.
 */

import QtQuick 2.1
import QtQuick.Controls 1.1
import board.core 2.0
import board.core.paint 2.0
import "sheet.js" as Js

Sheet {
    id: sheet
    anchors.fill: parent
    enabled: visible

    Rectangle {
        z: -1
        anchors.fill: parent
        color: sheet.color

        Image {
            anchors.fill: parent
            source: sheet.imageSource
            visible: sheet.imageSource ? true : false
            fillMode: sheet.imageMode == 1 ? Image.Stretch : sheet.imageMode == 2 ? Image.Tile : Image.PreserveAspectFit
        }
    }

    SheetCanvas {
        id: sheetCanvas
        objectName: "sheetCanvas"
        anchors.left: parent.left
        anchors.top: parent.top
        anchors.right: vscroll.visible ? vscroll.left : parent.right
        anchors.bottom: hscroll.visible ? hscroll.top : parent.bottom
        clip: true

        Item {
            id: container
            objectName: "container"
            anchors.fill: parent

            transform: Scale {
                xScale: Paint.scale
                yScale: Paint.scale
            }
        }

        Rectangle {
            id: selectRect
            objectName: "selectRect"
            z: 1
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
                                                                         modelData[0] === 0,
                                                                         modelData[1] === 0,
                                                                         modelData[0] === 1,
                                                                         modelData[1] === 1)
                        onReleased: if (selectRect.selectGen)
                                        selectRect.selectGen.onScaleEnd()
                        onPositionChanged: if (selectRect.selectGen)
                                               selectRect.selectGen.onScale(mouse.x, mouse.y)
                    }
                }
            }
        }

        Rectangle {
            id: eraseRect
            z: 1
            x: sheetCanvas.mouseX - Paint.eraserSize
            y: sheetCanvas.mouseY - Paint.eraserSize
            width: Paint.eraserSize * 2
            height: Paint.eraserSize * 2
            color: "transparent"
            border.width: 1
            border.color: "black"
            visible: Paint.mode == "eraser" && sheetCanvas.containsMouse
        }

        Item {
            id: textInputItem
            width: textInput.width * textInputScale.xScale
            height: textInput.height * textInputScale.yScale
            visible: false

            function updatePos() {
                var textItem = textInput.textItem
                var pos = sheetCanvas.mapFromItem(container, textItem.x, textItem.y)
                textInputItem.x = pos.x
                textInputItem.y = pos.y
                textInputScale.xScale = textItem.scalex * Paint.scale
                textInputScale.yScale = textItem.scaley * Paint.scale
            }

            Connections {
                target: Paint
                onScaleChanged: {
                    if (textInput.textItem) {
                        textInputItem.updatePos()
                    }
                }
            }

            Connections {
                target: sheetCanvas
                onSheetPointChanged: {
                    if (textInput.textItem) {
                        textInputItem.updatePos()
                    }
                }
            }

            TextEdit {
                id: textInput
                objectName: "textInput"
                property variant textGen
                property variant textItem
                width: contentWidth
                height: contentHeight
                textFormat: TextEdit.RichText
                selectByMouse: true
                transform: Scale {
                    id: textInputScale
                }

                onTextItemChanged: {
                    if (textItem) {
                        textInputItem.updatePos()
                        textInputItem.visible = true
                        font.family = textItem.fontFamily
                        font.pixelSize = textItem.fontSize
                        color = textItem.color
                        textInputScale.xScale = textItem.scalex * Paint.scale
                        textInputScale.yScale = textItem.scaley * Paint.scale
                        text = textItem.text
                        cursorPosition = positionAt((sheetCanvas.mouseX - textItem.x) / textItem.scalex,
                                                    (sheetCanvas.mouseY - textItem.y) / textItem.scaley)
                        TextEditTool.init(textInput.textDocument)
                        TextEditTool.selectionStart = textInput.selectionStart
                        TextEditTool.selectionEnd = textInput.selectionEnd
                        TextEditTool.bold = boldButton.checked
                        TextEditTool.italic = italicButton.checked
                        TextEditTool.underline = underlineButton.checked
                        Core.keyboard = true
                    }
                    else {
                        textInputItem.visible = false;
                        Core.keyboard = false;
                        TextEditTool.init(null);
                    }
                }

                onSelectionStartChanged: TextEditTool.selectionStart = selectionStart
                onSelectionEndChanged: TextEditTool.selectionEnd = selectionEnd
            }

            Rectangle {
                anchors.fill: parent
                color: "transparent"
                border.color: "black"
                border.width: 2
                anchors.margins: -5
            }

            Row {
                x: 0
                y: -Style.buttonSize - 4
                spacing: 4

                Button {
                    id: boldButton
                    width: Style.buttonSize
                    height: Style.buttonSize
                    style: Style.normalButton
                    checkable: true
                    iconSource: "qrc:/core/res/bold.svg"
                    onCheckedChanged: TextEditTool.bold = checked
                }

                Button {
                    id: italicButton
                    width: Style.buttonSize
                    height: Style.buttonSize
                    style: Style.normalButton
                    checkable: true
                    iconSource: "qrc:/core/res/italic.svg"
                    onCheckedChanged: TextEditTool.italic = checked
                }

                Button {
                    id: underlineButton
                    width: Style.buttonSize
                    height: Style.buttonSize
                    style: Style.normalButton
                    checkable: true
                    iconSource: "qrc:/core/res/underline.svg"
                    onCheckedChanged: TextEditTool.underline = checked
                }
            }
        }
    }

    ScrollBar {
        id: vscroll
        horizontal: false
        anchors.top: parent.top
        anchors.right: parent.right
        anchors.bottom: hscroll.top
        visible: sheet.scrollable
        width: 20
        onLeftButton: sheetCanvas.moveSheet(0, -10)
        onRightButton: sheetCanvas.moveSheet(0, 10)
        onLeftPage: sheetCanvas.moveSheet(0, -sheetCanvas.height / Paint.scale / 2)
        onRightPage: sheetCanvas.moveSheet(0, sheetCanvas.height / Paint.scale / 2)
        onMove: sheetCanvas.moveSheet(0, sheetCanvas.height * step)

        function updateScroll() {
            position = -sheetCanvas.sheetRect.y / sheetCanvas.sheetRect.height;
            length = sheetCanvas.height / Paint.scale / sheetCanvas.sheetRect.height;
        }
    }

    ScrollBar {
        id: hscroll
        horizontal: true
        anchors.left: parent.left
        anchors.right: vscroll.left
        anchors.bottom: parent.bottom
        visible: sheet.scrollable
        height: 20
        onLeftButton: sheetCanvas.moveSheet(-10, 0)
        onRightButton: sheetCanvas.moveSheet(10, 0)
        onLeftPage: sheetCanvas.moveSheet(-sheetCanvas.width / Paint.scale / 2, 0)
        onRightPage: sheetCanvas.moveSheet(sheetCanvas.width / Paint.scale / 2, 0)
        onMove: sheetCanvas.moveSheet(sheetCanvas.width * step, 0)

        function updateScroll() {
            position = -sheetCanvas.sheetRect.x / sheetCanvas.sheetRect.width;
            length = sheetCanvas.width / Paint.scale / sheetCanvas.sheetRect.width;
        }
    }

    Connections {
        target: sheetCanvas
        onSheetRectChanged: {
            vscroll.updateScroll()
            hscroll.updateScroll()
        }
    }
}
