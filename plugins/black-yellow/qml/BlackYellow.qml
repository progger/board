/*
 * Copyright (C) 2014 Michael Kulabuhov, Kemerovo, Russia.
 *
 * See the LICENSE file for terms of use.
 */

import QtQuick 2.2
import QtQuick.Controls 1.0
import board.core 2.0
import board.blackyellow 2.0

BlackYellow {
    id: blackYellow

    Rectangle {
        anchors.fill: parent
        color: "#804020"
        radius: 16

        Item {
            anchors.fill: parent
            anchors.margins: 18
            clip: true

            Rectangle {
                anchors.left: parent.left
                anchors.right: parent.horizontalCenter
                anchors.top: parent.top
                anchors.bottom: parent.bottom
                color: "black"
            }

            Rectangle {
                anchors.left: parent.horizontalCenter
                anchors.right: parent.right
                anchors.top: parent.top
                anchors.bottom: parent.bottom
                color: "yellow"
            }

            Item {
                anchors.fill: parent
                anchors.margins: 16

                Column {
                    id: column

                    Repeater {
                        model: blackYellow.items

                        Item {
                            width: Math.max(questionText.width, answerText.width)
                            height: questionText.height + answerText.height

                            Drag.active: dragArea.drag.active
                            Drag.hotSpot.x: width / 2
                            Drag.hotSpot.y: height / 2

                            TextEdit {
                                id: questionText
                                anchors.top: parent.top
                                anchors.horizontalCenter: parent.horizontalCenter
                                width: contentWidth
                                height: contentHeight
                                color: editButton.checked ? "#909000" : "#FFFF00"
                                font.pixelSize: 35
                                readOnly: !editButton.checked
                                text: modelData.question
                                onTextChanged: {
                                    modelData.question = text
                                    blackYellow.saveItems()
                                }
                            }

                            TextEdit {
                                id: answerText
                                anchors.top: questionText.bottom
                                anchors.horizontalCenter: parent.horizontalCenter
                                width: contentWidth
                                height: contentHeight
                                color: editButton.checked ? "#606060" : "#000000"
                                font.pixelSize: 35
                                readOnly: !editButton.checked
                                text: modelData.answer
                                onTextChanged: {
                                    modelData.answer = text
                                    blackYellow.saveItems()
                                }
                            }

                            MouseArea {
                                id: dragArea
                                anchors.fill: parent
                                enabled: !editButton.checked
                                drag.target: parent
                                onReleased: parent.Drag.drop()
                            }

                            Button {
                                anchors.left: parent.right
                                anchors.verticalCenter: parent.verticalCenter
                                anchors.leftMargin: 8
                                width: Style.buttonSize
                                height: Style.buttonSize
                                style: Style.normalButton
                                visible: editButton.checked
                                iconSource: "qrc:/core/res/delete.svg"
                                tooltip: "Удалить"
                                onClicked: blackYellow.removeItem(index)
                            }
                        }
                    }

                    Button {
                        width: Style.buttonSize
                        height: Style.buttonSize
                        style: Style.normalButton
                        visible: editButton.checked
                        iconSource: "qrc:/core/res/add.svg"
                        tooltip: "Добавить"
                        onClicked: blackYellow.addItem()
                    }
                }
            }

            Button {
                id: editButton
                anchors.top: parent.top
                anchors.right: parent.right
                width: Style.buttonSize
                height: Style.buttonSize
                checkable: true
                style: Style.normalButton
                iconSource: "qrc:/core/res/pen.svg"
                tooltip: "Редактировать"
            }
        }
    }
}
