/*
 * Copyright (C) 2011 Kulabuhov Michail, Kemerovo, Russia.
 *
 * See the LICENSE file for terms of use.
 */

import QtQuick 1.1
import "colorSelector.js" as Script

Rectangle {
    id: colorSelector
    property variant style
    property int selected: 0
    property int numButtons: 4
    property int buttonSize: height - 8

    Row {
        x: 4
        anchors.top: parent.top
        anchors.bottom: parent.bottom
        spacing: 4

        Repeater {
            id: repeater
            model: numButtons

            Rectangle {
                property real freq: 1
                anchors.verticalCenter: parent.verticalCenter
                height: buttonSize
                width: buttonSize
                border.width: index == selected ? 4 : 0
                border.color: "black"
                radius: 4
                color: Script.colors[index].color

                MouseArea {
                    anchors.fill: parent
                    onClicked: Script.changeColor(index)
                    onDoubleClicked: Script.selectCustomColor(index)
                }
            }
        }

        Button {
            style: colorSelector.style
            anchors.verticalCenter: parent.verticalCenter
            width: 24
            height: parent.height - 6
            image: "qrc:/res/more.svg"
            toggled: colorGridRect.opacity
            onClicked: Script.moreClick()
        }
    }

    Rectangle {
        id: colorGridRect
        anchors.left: parent.left
        anchors.top: parent.bottom
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
            model: colorGridModel
            width: cellWidth * numButtons
            height: cellHeight * Math.ceil(colorGridModel.count / numButtons)
            delegate: colorGridDelegate

            ListModel {
                id: colorGridModel
            }

            Component {
                id: colorGridDelegate
                Rectangle {
                    height: buttonSize
                    width: buttonSize
                    color: model.color

                    MouseArea {
                        anchors.fill: parent
                        onClicked: Script.selectColor(color)
                    }
                }
            }
        }
    }
}
