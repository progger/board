/*
 * Copyright (C) 2012 Michael Kulabuhov, Kemerovo, Russia.
 *
 * See the LICENSE file for terms of use.
 */

import QtQuick 2.1
import QtQuick.Controls 1.0
import QtQuick.Dialogs 1.0
import board.core 2.0

Rectangle {
    id: toolBar
    property int buttonSize: height - 6
    color: Style.panelColor

    Item {
        anchors.left: parent.left
        anchors.top: parent.top
        anchors.right: saveBookButton.left
        anchors.bottom: parent.bottom
        anchors.rightMargin: 12

        Component {
            id: tab

            Item {
                id: item
                width: height
                height: toolBar.height
                ListView.onCurrentItemChanged: modelData.visible = ListView.isCurrentItem

                Text {
                    anchors.centerIn: parent
                    font.pixelSize: parent.height / 2
                    text: index + 1
                }

                MouseArea {
                    anchors.fill: parent
                    acceptedButtons: Qt.LeftButton | Qt.RightButton
                    onClicked: clickedFunc(mouse)

                    function clickedFunc(mouse) {
                        listView.currentIndex = index;
                        if (mouse.button === Qt.RightButton) {
                            sheetMenu.x = mouse.x + item.x - 4;
                            sheetMenu.y = mouse.y - 4;
                            sheetMenu.enabled = true;
                        }
                    }
                }
            }
        }

        ListView {
            id: listView
            anchors.fill: parent
            model: Core.sheets
            orientation: ListView.Horizontal
            delegate: tab
            highlight: Rectangle { color: "blue" }
            clip: true
            onCurrentIndexChanged: Core.sheetIndex = currentIndex
        }

        PopupMenu {
            id: sheetMenu
            z: 1
            items: [
                QtObject {
                    property string name: "Добавить перед"
                    function onClicked() {
                        var index = listView.currentIndex;
                        Core.insertSheet(index);
                        listView.currentIndex = index + 1;
                        sheetMenu.enabled = false;
                    }
                },
                QtObject {
                    property string name: "Добавить после"
                    function onClicked() {
                        var index = listView.currentIndex;
                        Core.insertSheet(index + 1);
                        listView.currentIndex = index;
                        sheetMenu.enabled = false;
                    }
                },
                QtObject {
                    property string name: "Удалить"
                    function onClicked() {
                        Core.deleteSheet(listView.currentIndex);
                        sheetMenu.enabled = false;
                    }
                }
            ]
        }
    }

    Rectangle {
        id: colorRect
        anchors.right: backgroundRect.left
        anchors.verticalCenter: parent.verticalCenter
        anchors.rightMargin: 4
        width: buttonSize
        height: buttonSize
        color: Paint.color
        border.width: 2
        border.color: "black"

        MouseArea {
            anchors.fill: parent
            onClicked: colorGridRect.opacity = !colorGridRect.opacity
        }

        ColorGrid {
            id: colorGridRect
            x: 0
            y: parent.height
            cellSize: buttonSize
            onSelect: Paint.color = color
        }
    }

    Rectangle {
        id: backgroundRect
        anchors.right: operationButtons.left
        anchors.verticalCenter: parent.verticalCenter
        anchors.rightMargin: 12
        width: buttonSize
        height: buttonSize
        color: Paint.bgcolor
        border.width: 2
        border.color: "black"

        MouseArea {
            anchors.fill: parent
            onClicked: backgroundGridRect.opacity = !backgroundGridRect.opacity
        }

        ColorGrid {
            id: backgroundGridRect
            x: 0
            y: parent.height
            cellSize: buttonSize
            onSelect: Paint.bgcolor = color
        }
    }

    Row {
        id: operationButtons
        anchors.right: saveBookButton.left
        anchors.verticalCenter: parent.verticalCenter
        anchors.rightMargin: 12
        height: parent.height
        spacing: 4

        Button {
            anchors.verticalCenter: parent.verticalCenter
            style: Style.normalButton
            width: buttonSize
            height: buttonSize
            tooltip: "отменить"
            iconSource: "qrc:/core/res/undo.svg"
            enabled: Paint.canUndo
            onClicked: Paint.undo()
        }

        Button {
            anchors.verticalCenter: parent.verticalCenter
            style: Style.normalButton
            width: buttonSize
            height: buttonSize
            tooltip: "вернуть"
            iconSource: "qrc:/core/res/redo.svg"
            enabled: Paint.canRedo
            onClicked: Paint.redo()
        }

        Button {
            anchors.verticalCenter: parent.verticalCenter
            style: Style.normalButton
            enabled: Paint.selected;
            width: buttonSize
            height: buttonSize
            tooltip: "удалить"
            iconSource: "qrc:/core/res/delete.svg"
            onClicked: Paint.del()
        }

        Button {
            anchors.verticalCenter: parent.verticalCenter
            style: Style.normalButton
            enabled: Paint.selected;
            width: buttonSize
            height: buttonSize
            tooltip: "дублировать"
            iconSource: "qrc:/core/res/duplicate.svg"
            onClicked: Paint.duplicate()
        }

        Button {
            anchors.verticalCenter: parent.verticalCenter
            style: Style.normalButton
            enabled: Paint.selected;
            width: buttonSize
            height: buttonSize
            tooltip: "на передний план"
            iconSource: "qrc:/core/res/to_front.svg"
            onClicked: Paint.toFront()
        }

        Button {
            anchors.verticalCenter: parent.verticalCenter
            style: Style.normalButton
            enabled: Paint.selected;
            width: buttonSize
            height: buttonSize
            tooltip: "на задний план"
            iconSource: "qrc:/core/res/to_back.svg"
            onClicked: Paint.toBack()
        }
    }

    Button {
        id: saveBookButton
        style: Style.normalButton
        anchors.right: openBookButton.left
        anchors.verticalCenter: parent.verticalCenter
        anchors.rightMargin: 4
        width: buttonSize
        height: buttonSize
        tooltip: "сохранить"
        iconSource: "qrc:/core/res/save.svg"
        onClicked: saveBookDialog.open()
    }

    Button {
        id: openBookButton
        style: Style.normalButton
        anchors.right: pluginsRow.left
        anchors.verticalCenter: parent.verticalCenter
        anchors.rightMargin: 12
        width: buttonSize
        height: buttonSize
        tooltip: "открыть"
        iconSource: "qrc:/core/res/open.svg"
        onClicked: openBookDialog.open()
    }

    Row {
        id: pluginsRow
        objectName: "pluginRow"
        anchors.right: thicknessImage.left
        anchors.verticalCenter: parent.verticalCenter
        anchors.rightMargin: 12
        height: parent.height
    }

    Image {
        id: thicknessImage
        anchors.right: thicknessSpinBox.left
        anchors.verticalCenter: parent.verticalCenter
        anchors.rightMargin: 4
        height: buttonSize
        width: buttonSize
        source: "qrc:/core/res/thickness.svg"
        smooth: true
    }

    SpinBoxEx {
            id: thicknessSpinBox
            anchors.right: fontSizeImage.left
            anchors.verticalCenter: parent.verticalCenter
            anchors.rightMargin: 12
            width: 60
            height: buttonSize
            onValueChanged: Paint.thickness = value
            step: 1
            minValue: 1
            maxValue: 10
            Component.onCompleted: value = Paint.thickness
        }

    Image {
        id: fontSizeImage
        anchors.right: fontSizeSpinBox.left
        anchors.verticalCenter: parent.verticalCenter
        anchors.rightMargin: 4
        height: buttonSize
        width: buttonSize
        source: "qrc:/core/res/font_size.svg"
        smooth: true
    }

    SpinBoxEx {
        id: fontSizeSpinBox
        width: 60
        anchors.right: transparentButton.left
        anchors.verticalCenter: parent.verticalCenter
        anchors.rightMargin: 12
        height: buttonSize
        onValueChanged: Paint.fontSize = value
        step: 2
        minValue: 10
        maxValue: 60
        Component.onCompleted: value = Paint.fontSize
    }

    Button {
        id: transparentButton
        style: Style.normalButton
        anchors.right: Core.windowMode ? parent.right : minimizeButton.left
        anchors.verticalCenter: parent.verticalCenter
        anchors.rightMargin: 4
        width: buttonSize
        height: buttonSize
        tooltip: "рабочий стол"
        iconSource: "qrc:/core/res/desktop.svg"
        checked: Core.transparent
        onClicked: Core.transparent = !Core.transparent
    }

    Button {
        id: minimizeButton
        style: Style.minimizeButton
        anchors.right: closeButton.left
        anchors.verticalCenter: parent.verticalCenter
        anchors.rightMargin: 4
        width: buttonSize
        height: buttonSize
        iconSource: "qrc:/core/res/minimize.svg"
        onClicked: Core.minimizeButton()
        visible: !Core.windowMode
    }

    Button {
        id: closeButton
        style: Style.closeButton
        anchors.right: parent.right
        anchors.verticalCenter: parent.verticalCenter
        anchors.rightMargin: 6
        width: buttonSize
        height: buttonSize
        iconSource: "qrc:/core/res/close.svg"
        onClicked: Core.quitButton()
        visible: !Core.windowMode
    }

    FileDialog {
        id: saveBookDialog
        modality: Qt.ApplicationModal
        nameFilters: ["Book files (*.brd)"]
        selectExisting: false
        title: "Сохранить книгу"
        onAccepted: Core.saveBook(fileUrl.toString().replace("file://", ""))
    }

    FileDialog {
        id: openBookDialog
        modality: Qt.ApplicationModal
        nameFilters: ["Book files (*.brd)"]
        selectExisting: true
        title: "Открыть книгу"
        onAccepted: Core.openBook(fileUrl.toString().replace("file://", ""))
    }
}
