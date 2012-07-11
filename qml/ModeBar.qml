/*
 * Copyright (C) 2012 Kulabuhov Michail, Kemerovo, Russia.
 *
 * See the LICENSE file for terms of use.
 */

import QtQuick 1.1

Rectangle {
    id: modeBar
    property variant style
    property int buttonSize: style.panelSize - 6
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
                [{"mode": "select", "image": "select.svg"},
                {"mode": "pen", "image": "pen.svg"}],
                [{"mode": "rectangle", "image": "rectangle.svg"},
                {"mode": "magic_pen", "image": "magic_pen.svg"}],
                [{"mode": "circle", "image": "circle.svg"},
                {"mode": "ellipse", "image": "ellipse.svg"}],
                [{"mode": "text", "image": "text.svg"},
                {"mode": "image", "image": "image.svg"}]
            ]

            Item {
                width: parent.width
                height: buttonSize

                Button {
                    style: modeBar.style.normalButton
                    x: parent.width * 0.25 - buttonSize / 2
                    width: buttonSize
                    height: buttonSize
                    image: "qrc:/res/" + modelData[0].image
                    toggled: Core.mode == modelData[0].mode
                    onClicked: Core.mode = modelData[0].mode
                }

                Button {
                    style: modeBar.style.normalButton
                    x: parent.width * 0.75 - buttonSize / 2
                    width: buttonSize
                    height: buttonSize
                    image: "qrc:/res/" + modelData[1].image
                    toggled: Core.mode == modelData[1].mode
                    onClicked: Core.mode = modelData[1].mode
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
                image: "qrc:/res/undo.svg"
                enabled: Core.canUndo
                onClicked: Core.undo()
            }

            Button {
                x: parent.width * 0.75 - buttonSize / 2
                style: modeBar.style.normalButton
                width: buttonSize
                height: buttonSize
                image: "qrc:/res/redo.svg"
                enabled: Core.canRedo
                onClicked: Core.redo()
            }
        }

        Item {
            width: parent.width
            height: buttonSize

            Button {
                x: parent.width * 0.25 - buttonSize / 2
                style: modeBar.style.normalButton
                enabled: Core.selected;
                width: buttonSize
                height: buttonSize
                image: "qrc:/res/delete.svg"
                onClicked: Core.del()
            }

            Button {
                x: parent.width * 0.75 - buttonSize / 2
                style: modeBar.style.normalButton
                enabled: Core.selected;
                width: buttonSize
                height: buttonSize
                image: "qrc:/res/duplicate.svg"
                onClicked: Core.duplicate()
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
                image: "qrc:/res/save.svg"
                onClicked: Core.save()
            }
        }
    }

    MouseArea {
        anchors.fill: parent
        drag.target: modeBar
        drag.minimumX: draw.x
        drag.maximumX: draw.x + draw.width - width
        drag.minimumY: draw.y
        drag.maximumY: draw.y + draw.height - height
    }
}
