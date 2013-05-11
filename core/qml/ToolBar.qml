/*
 * Copyright (C) 2012 Kulabuhov Michail, Kemerovo, Russia.
 *
 * See the LICENSE file for terms of use.
 */

import QtQuick 2.0
import board.core.paint 1.0

Rectangle {
    id: toolBar
    property variant style: board.style
    property int buttonSize: height - 6
    color: style.panelColor

    Item {
        anchors.left: parent.left
        anchors.top: parent.top
        anchors.bottom: parent.bottom
        width: parent.width / 3

        Component {
            id: tab

            Item {
                width: height
                height: toolBar.height
                property variant sheet
                Component.onCompleted: sheet = sheetComponent.createObject(sheetPlace, {visible: false})
                Component.onDestruction: sheet.destroy()
                ListView.onIsCurrentItemChanged: sheet.visible = ListView.isCurrentItem

                Text {
                    anchors.centerIn: parent
                    font.pixelSize: parent.height / 2
                    text: index + 1
                }

                MouseArea {
                    anchors.fill: parent
                    onClicked: listView.currentIndex = index
                }
            }
        }

        ListModel {
            id: listModel
            Component.onCompleted: {
                for (var i = 0; i < 5; ++i)
                    listModel.append({});
            }
        }

        ListView {
            id: listView
            anchors.fill: parent
            model: listModel
            orientation: ListView.Horizontal
            delegate: tab
            highlight: Rectangle { color: "blue" }
            clip: true
        }
    }

    Row {
        anchors.right: parent.right
        anchors.top: parent.top
        anchors.bottom: parent.bottom
        spacing: 4

        Image {
            anchors.verticalCenter: parent.verticalCenter
            height: buttonSize
            width: buttonSize
            source: "qrc:/core/res/thickness.svg"
            smooth: true
        }

        SpinBox {
            style: toolBar.style
            anchors.verticalCenter: parent.verticalCenter
            width: 60
            height: buttonSize
            onValueChanged: Paint.thickness = value
            step: 1
            minValue: 1
            maxValue: 10
            Component.onCompleted: value = Paint.thickness
        }

        Item {
            width: 8
            height: parent.height
        }

        Image {
            anchors.verticalCenter: parent.verticalCenter
            height: buttonSize
            width: buttonSize
            source: "qrc:/core/res/font_size.svg"
            smooth: true
        }

        SpinBox {
            style: toolBar.style
            width: 60
            anchors.verticalCenter: parent.verticalCenter
            height: buttonSize
            onValueChanged: Paint.fontSize = value
            step: 2
            minValue: 10
            maxValue: 60
            Component.onCompleted: value = Paint.fontSize
        }

        Item {
            width: 8
            height: parent.height
        }

        Button {
            id: minimizeButton
            style: board.style.minimizeButton
            anchors.verticalCenter: parent.verticalCenter
            width: buttonSize
            height: buttonSize
            image: "qrc:/core/res/minimize.svg"
            onClicked: Core.minimizeButton();
        }

        Button {
            id: closeButton
            style: board.style.closeButton
            anchors.verticalCenter: parent.verticalCenter
            width: buttonSize
            height: buttonSize
            image: "qrc:/core/res/close.svg"
            onClicked: Core.quitButton();
        }

        Item {
            width: 1
            height: parent.height
        }
    }
}
