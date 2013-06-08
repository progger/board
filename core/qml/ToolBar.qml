/*
 * Copyright (C) 2012 Kulabuhov Michail, Kemerovo, Russia.
 *
 * See the LICENSE file for terms of use.
 */

import QtQuick 2.0

Rectangle {
    id: toolBar
    property variant style: board.style
    property int buttonSize: height - 6
    color: style.panelColor

    Item {
        anchors.left: parent.left
        anchors.top: parent.top
        anchors.right: saveBookButton.left
        anchors.bottom: parent.bottom
        anchors.rightMargin: 12

        Component {
            id: tab

            Item {
                width: height
                height: toolBar.height
                ListView.onIsCurrentItemChanged: modelData.visible = ListView.isCurrentItem

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

        ListView {
            id: listView
            anchors.fill: parent
            model: Core.sheets
            orientation: ListView.Horizontal
            delegate: tab
            highlight: Rectangle { color: "blue" }
            clip: true
        }
    }

    Button {
        id: saveBookButton
        style: board.style.normalButton
        anchors.right: openBookButton.left
        anchors.verticalCenter: parent.verticalCenter
        anchors.rightMargin: 4
        width: buttonSize
        height: buttonSize
        image: "qrc:/core/res/save.svg"
        onClicked: Core.saveBook()
    }

    Button {
        id: openBookButton
        style: board.style.normalButton
        anchors.right: thicknessImage.left
        anchors.verticalCenter: parent.verticalCenter
        anchors.rightMargin: 12
        width: buttonSize
        height: buttonSize
        image: "qrc:/core/res/open.svg"
        onClicked: Core.openBook()
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

    SpinBox {
        id: thicknessSpinBox
        style: toolBar.style
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

    SpinBox {
        id: fontSizeSpinBox
        style: toolBar.style
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
        style: board.style.normalButton
        anchors.right: minimizeButton.left
        anchors.verticalCenter: parent.verticalCenter
        anchors.rightMargin: 4
        width: buttonSize
        height: buttonSize
        image: "qrc:/core/res/desktop.svg"
        toggled: Core.transparent
        onClicked: Core.transparent = !Core.transparent
    }

    Button {
        id: minimizeButton
        style: board.style.minimizeButton
        anchors.right: closeButton.left
        anchors.verticalCenter: parent.verticalCenter
        anchors.rightMargin: 4
        width: buttonSize
        height: buttonSize
        image: "qrc:/core/res/minimize.svg"
        onClicked: Core.minimizeButton()
    }

    Button {
        id: closeButton
        style: board.style.closeButton
        anchors.right: parent.right
        anchors.verticalCenter: parent.verticalCenter
        anchors.rightMargin: 6
        width: buttonSize
        height: buttonSize
        image: "qrc:/core/res/close.svg"
        onClicked: Core.quitButton()
    }
}
