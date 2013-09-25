/*
 * Copyright (C) 2012 Michael Kulabuhov, Kemerovo, Russia.
 *
 * See the LICENSE file for terms of use.
 */

import QtQuick 2.0
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
                    border.color: "silver"
                    border.width: 2
                    width: buttonSize
                    height: buttonSize
                    hint: modelData.hint
                    image: modelData.image
                    toggled: Paint.mode == modelData.mode
                    onClicked: Paint.mode = modelData.mode
                }
            }
        }

        Button {
            anchors.horizontalCenter: parent.horizontalCenter
            style: Style.normalButton
            border.color: "silver"
            border.width: 2
            width: buttonSize
            height: buttonSize
            hint: "картинка"
            image: "qrc:/core/res/image.svg"
            toggled: Paint.mode == "image"
            onClicked: Paint.selectImage()
        }

        Button {
            anchors.horizontalCenter: parent.horizontalCenter
            style: Style.normalButton
            border.color: "silver"
            border.width: 2
            width: buttonSize
            height: buttonSize
            hint: "видео"
            image: "qrc:/core/res/video.svg"
            toggled: Paint.mode == "video"
            onClicked: Paint.selectVideo()
        }

        Button {
            id: colorButton
            anchors.horizontalCenter: parent.horizontalCenter
            style: Style.normalButton
            border.color: "silver"
            border.width: 2
            width: buttonSize
            height: buttonSize
            hint: "выбор цвета"
            image: "qrc:/core/res/color.svg"
            toggled: colorGridRect.opacity
            onClicked: colorGridRect.opacity = !colorGridRect.opacity
        }
    }

    Rectangle {
        id: colorGridRect
        z: 1
        x: parent.width
        y: colorButton.y + colorButton.height + column.y - height
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
            cellWidth: buttonSize + 4
            cellHeight: buttonSize + 4
            model: [
                "#000000", "#ff0000", "#00ff00", "#0000ff",
                "#ffff00", "#ff00ff", "#00ffff", "#800000",
                "#008000", "#000080", "#808000", "#800080",
                "#008080", "#808080"
            ]
            width: cellWidth * 4
            height: cellHeight * 4
            delegate: colorGridDelegate

            Component {
                id: colorGridDelegate
                Rectangle {
                    height: buttonSize
                    width: buttonSize
                    color: modelData

                    MouseArea {
                        anchors.fill: parent
                        onClicked: {
                            Paint.color = modelData;
                            colorGridRect.opacity = 0;
                        }
                    }
                }
            }
        }
    }

    MouseArea {
        anchors.fill: parent
        drag.target: modeBar
        drag.minimumX: 0
        drag.maximumX: board.width - width
        drag.minimumY: 0
        drag.maximumY: board.height - height
    }
}
