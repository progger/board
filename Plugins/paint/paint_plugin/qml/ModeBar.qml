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
    x: 10
    y: (parent.height - height) / 2
    width:  style.panelSize
    height: column.height + 20
    color: style.panelColor
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
                {"mode": "select", "image": "qrc:/core/res/select.svg"},
                {"mode": "pen", "image": "qrc:/plugin/paint/res/pen.svg"},
                {"mode": "rectangle", "image": "qrc:/plugin/paint/res/rectangle.svg"},
                {"mode": "magic_pen", "image": "qrc:/plugin/paint/res/magic_pen.svg"},
                {"mode": "circle", "image": "qrc:/plugin/paint/res/circle.svg"},
                {"mode": "ellipse", "image": "qrc:/plugin/paint/res/ellipse.svg"},
                {"mode": "text", "image": "qrc:/plugin/paint/res/text.svg"},
                {"mode": "image", "image": "qrc:/plugin/paint/res/image.svg"}
            ]

            Item {
                width: parent.width
                height: buttonSize

                Button {
                    anchors.horizontalCenter: parent.horizontalCenter
                    style: modeBar.style.normalButton
                    border.color: "silver"
                    border.width: 2
                    width: buttonSize
                    height: buttonSize
                    image: modelData.image
                    toggled: Paint.mode == modelData.mode
                    onClicked: Paint.mode = modelData.mode
                }
            }
        }

        Button {
            anchors.horizontalCenter: parent.horizontalCenter
            style: modeBar.style.normalButton
            border.color: "silver"
            border.width: 2
            width: buttonSize
            height: buttonSize
            image: "qrc:/core/res/undo.svg"
            enabled: Paint.canUndo
            onClicked: Paint.undo()
        }

        Button {
            anchors.horizontalCenter: parent.horizontalCenter
            style: modeBar.style.normalButton
            border.color: "silver"
            border.width: 2
            width: buttonSize
            height: buttonSize
            image: "qrc:/core/res/redo.svg"
            enabled: Paint.canRedo
            onClicked: Paint.redo()
        }

        Button {
            anchors.horizontalCenter: parent.horizontalCenter
            style: modeBar.style.normalButton
            border.color: "silver"
            border.width: 2
            enabled: Paint.selected;
            width: buttonSize
            height: buttonSize
            image: "qrc:/core/res/delete.svg"
            onClicked: Paint.del()
        }

        Button {
            anchors.horizontalCenter: parent.horizontalCenter
            style: modeBar.style.normalButton
            border.color: "silver"
            border.width: 2
            enabled: Paint.selected;
            width: buttonSize
            height: buttonSize
            image: "qrc:/plugin/paint/res/duplicate.svg"
            onClicked: Paint.duplicate()
        }

        Button {
            id: colorButton
            anchors.horizontalCenter: parent.horizontalCenter
            style: modeBar.style.normalButton
            border.color: "silver"
            border.width: 2
            width: buttonSize
            height: buttonSize
            image: "qrc:/plugin/paint/res/color.svg"
            toggled: colorGridRect.opacity
            onClicked: colorGridRect.opacity = !colorGridRect.opacity
        }

        Button {
            anchors.horizontalCenter: parent.horizontalCenter
            style: modeBar.style.normalButton
            border.color: "silver"
            border.width: 2
            width: buttonSize
            height: buttonSize
            image: "qrc:/core/res/save.svg"
            onClicked: Paint.save()
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
