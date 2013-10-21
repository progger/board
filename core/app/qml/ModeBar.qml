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
    id: modeBar
    property int buttonSize: Style.panelSize - 6
    width:  Style.panelSize
    height: column.height + 20
    color: "white"
    radius: 10
    border.color: "silver"
    border.width: 2

    Column {
        id: column
        y: 10
        z: 1
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.margins: 1
        spacing: 4

        Repeater {
            model: [
                {"mode": "select", "image": "qrc:/core/res/select.svg", "hint": "выбор"},
                {"mode": "pen", "image": "qrc:/core/res/pen.svg", "hint": "карандаш"},
                {"mode": "line", "image": "qrc:/core/res/line.svg", "hint": "линия"},
                {"mode": "rectangle", "image": "qrc:/core/res/rectangle.svg", "hint": "прямоугольник"},
                {"mode": "magic_pen", "image": "qrc:/core/res/magic_pen.svg", "hint": "магический карандаш"},
                {"mode": "circle", "image": "qrc:/core/res/circle.svg", "hint": "круг"},
                {"mode": "ellipse", "image": "qrc:/core/res/ellipse.svg", "hint": "эллипс"},
                {"mode": "text", "image": "qrc:/core/res/text.svg", "hint": "текст"},
                {"mode": "move", "image": "qrc:/core/res/move.svg", "hint": "движение"}
            ]

            Item {
                width: parent.width
                height: buttonSize

                Button {
                    anchors.horizontalCenter: parent.horizontalCenter
                    style: Style.normalButton
                    width: buttonSize
                    height: buttonSize
                    tooltip: modelData.hint
                    iconSource: modelData.image
                    checked: Paint.mode == modelData.mode
                    onClicked: Paint.mode = modelData.mode
                }
            }
        }

        Button {
            anchors.horizontalCenter: parent.horizontalCenter
            style: Style.normalButton
            width: buttonSize
            height: buttonSize
            tooltip: "картинка"
            iconSource: "qrc:/core/res/image.svg"
            checked: Paint.mode == "image"
            onClicked: openImageDialog.open()
        }

        Button {
            anchors.horizontalCenter: parent.horizontalCenter
            style: Style.normalButton
            width: buttonSize
            height: buttonSize
            tooltip: "видео"
            iconSource: "qrc:/core/res/video.svg"
            checked: Paint.mode == "video"
            onClicked: openVideoDialog.open()
        }

        Button {
            id: colorButton
            anchors.horizontalCenter: parent.horizontalCenter
            style: Style.normalButton
            width: buttonSize
            height: buttonSize
            tooltip: "выбор цвета"
            iconSource: "qrc:/core/res/color.svg"
            checked: colorGridRect.opacity
            onClicked: colorGridRect.opacity = !colorGridRect.opacity
        }
    }

    ColorGrid {
        id: colorGridRect
        z: 1
        x: parent.width
        y: colorButton.y + colorButton.height + column.y - height
        cellSize: buttonSize
        onSelect: Paint.color = color
    }

    MouseArea {
        anchors.fill: parent
        drag.target: modeBar
        drag.minimumX: 0
        drag.maximumX: board.width - width
        drag.minimumY: 0
        drag.maximumY: board.height - height
    }

    FileDialog {
        id: openImageDialog
        modality: Qt.ApplicationModal
        nameFilters: ["Image files (*.png *.jpg *.jpeg *.tif *.tiff *.gif *.svg)"]
        selectExisting: true
        title: "Открыть изображение"
        onAccepted: Paint.selectImage(fileUrl.toString().replace("file://", ""))
    }

    FileDialog {
        id: openVideoDialog
        modality: Qt.ApplicationModal
        //nameFilters: ["Video files (*.avi)"] //TODO
        selectExisting: true
        title: "Открыть видео"
        onAccepted: Paint.selectVideo(fileUrl)
    }
}
