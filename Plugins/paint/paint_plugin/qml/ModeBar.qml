/*
 * Copyright (C) 2012 Kulabuhov Michail, Kemerovo, Russia.
 *
 * See the LICENSE file for terms of use.
 */

import QtQuick 1.1
import ":/core/qml"

Rectangle {
    id: modeBar
    z: 7
    property variant style: board.style
    property int buttonSize: style.panelSize - 6
    x: parent.width - width * 1.5;
    y: parent.height / 3 - height / 2;
    width:  style.panelSize * 2
    height: column.y + column.height + 4
    color: style.panelColor
    border.color: "black"
    border.width: 2

    Rectangle {
        anchors.top: parent.top
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.margins: 2
        height: 16
        color: "blue"
    }

    Column {
        id: column
        y: 20
        z: 1
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.margins: 2
        spacing: 4

        Repeater {
            model: [
                [{"mode": "select", "image": "qrc:/core/res/select.svg"},
                {"mode": "pen", "image": "qrc:/plugin/res/pen.svg"}],
                [{"mode": "rectangle", "image": "qrc:/plugin/res/rectangle.svg"},
                {"mode": "magic_pen", "image": "qrc:/plugin/res/magic_pen.svg"}],
                [{"mode": "circle", "image": "qrc:/plugin/res/circle.svg"},
                {"mode": "ellipse", "image": "qrc:/plugin/res/ellipse.svg"}],
                [{"mode": "text", "image": "qrc:/plugin/res/text.svg"},
                {"mode": "image", "image": "qrc:/plugin/res/image.svg"}]
            ]

            Item {
                width: parent.width
                height: buttonSize

                Button {
                    style: modeBar.style.normalButton
                    x: parent.width * 0.25 - buttonSize / 2
                    width: buttonSize
                    height: buttonSize
                    image: modelData[0].image
                    toggled: Paint.mode == modelData[0].mode
                    onClicked: Paint.mode = modelData[0].mode
                }

                Button {
                    style: modeBar.style.normalButton
                    x: parent.width * 0.75 - buttonSize / 2
                    width: buttonSize
                    height: buttonSize
                    image: modelData[1].image
                    toggled: Paint.mode == modelData[1].mode
                    onClicked: Paint.mode = modelData[1].mode
                }
            }
        }

        Item {
            width: parent.width
            height: buttonSize

            Button {
                x: parent.width * 0.25 - buttonSize / 2
                style: modeBar.style.normalButton
                width: buttonSize
                height: buttonSize
                image: "qrc:/core/res/undo.svg"
                enabled: Paint.canUndo
                onClicked: Paint.undo()
            }

            Button {
                x: parent.width * 0.75 - buttonSize / 2
                style: modeBar.style.normalButton
                width: buttonSize
                height: buttonSize
                image: "qrc:/core/res/redo.svg"
                enabled: Paint.canRedo
                onClicked: Paint.redo()
            }
        }

        Item {
            width: parent.width
            height: buttonSize

            Button {
                x: parent.width * 0.25 - buttonSize / 2
                style: modeBar.style.normalButton
                enabled: Paint.selected;
                width: buttonSize
                height: buttonSize
                image: "qrc:/core/res/delete.svg"
                onClicked: Paint.del()
            }

            Button {
                x: parent.width * 0.75 - buttonSize / 2
                style: modeBar.style.normalButton
                enabled: Paint.selected;
                width: buttonSize
                height: buttonSize
                image: "qrc:/plugin/res/duplicate.svg"
                onClicked: Paint.duplicate()
            }
        }

        Item {
            width: parent.width
            height: buttonSize

            Button {
                id: colorButton
                x: parent.width * 0.25 - buttonSize / 2
                style: modeBar.style.normalButton
                width: buttonSize
                height: buttonSize
                image: "qrc:/plugin/res/color.svg"
                toggled: colorGridRect.opacity
                onClicked: colorGridRect.opacity = !colorGridRect.opacity
            }

            Button {
                x: parent.width * 0.75 - buttonSize / 2
                style: modeBar.style.normalButton
                width: buttonSize
                height: buttonSize
                image: "qrc:/core/res/save.svg"
                onClicked: Paint.save()
            }
        }
    }

    Rectangle {
        id: colorGridRect
        z: 1
        x: -width
        y: colorButton.parent.y + column.y
        border.color: "#404040"
        border.width: 2
        width: colorGrid.width + 4
        height: colorGrid.height + 4
        color: "#E0E0E0"
        opacity: 0
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
