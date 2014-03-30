/*
 * Copyright (C) 2014 Michael Kulabuhov, Kemerovo, Russia.
 *
 * See the LICENSE file for terms of use.
 */

import QtQuick 2.2
import QtQuick.Controls 1.0
import board.core 2.0
import board.arithmetic 2.0

Arithmetic {
    id: arithmetic
    property bool editMode: false

    Rectangle {
        anchors.fill: parent
        color: "#804020"
        radius: 16

        Rectangle {
            anchors.fill: parent
            anchors.margins: 16
            color: "#206020"
            clip: true
            radius: 12

            Component {
                id: listItem

                Item {
                    height: 40
                    width: resultText.x + Math.max(resultText.width, questionText.width)

                    MouseArea {
                        anchors.fill: parent
                        cursorShape: Qt.ArrowCursor
                    }

                    TextInput {
                        id: leftText
                        anchors.left: parent.left
                        width: contentWidth
                        height: parent.height
                        font.pixelSize: height * 0.8
                        readOnly: !editButton.checked
                        color: !editButton.checked ? "white" : "yellow"
                        text: model.left
                        validator: IntValidator {
                            bottom: -1000000
                            top: 1000000
                        }
                        onEditingFinished: {
                            model.left = text
                            arithmetic.saveItems()
                        }
                    }

                    TextInput {
                        id: operationText
                        anchors.left: leftText.right
                        anchors.leftMargin: 8
                        width: contentWidth
                        height: parent.height
                        font.pixelSize: height * 0.8
                        readOnly: !editButton.checked
                        color: !editButton.checked ? "white" : "yellow"
                        text: model.operation
                        validator: RegExpValidator {
                            regExp: /[+/-*/]/
                        }
                        onEditingFinished: {
                            model.operation = text
                            arithmetic.saveItems()
                        }
                    }

                    TextInput {
                        id: rightText
                        anchors.left: operationText.right
                        anchors.leftMargin: 8
                        width: contentWidth
                        height: parent.height
                        font.pixelSize: height * 0.8
                        readOnly: !editButton.checked
                        color: !editButton.checked ? "white" : "yellow"
                        text: model.right
                        validator: IntValidator {
                            bottom: -1000000
                            top: 1000000
                        }
                        onEditingFinished: {
                            model.right = text
                            arithmetic.saveItems()
                        }
                    }

                    Text {
                        id: equalText
                        anchors.left: rightText.right
                        anchors.leftMargin: 8
                        width: contentWidth
                        height: parent.height
                        font.pixelSize: height * 0.8
                        color: !editButton.checked ? "white" : "yellow"
                        text: "="
                    }

                    TextInput {
                        id: resultText
                        anchors.left: equalText.right
                        anchors.leftMargin: 8
                        width: questionText.width + contentWidth
                        height: parent.height
                        font.pixelSize: height * 0.8
                        color: "white"
                        visible: !editButton.checked
                        validator: IntValidator {
                            bottom: -1000000
                            top: 1000000
                        }
                        onEditingFinished: checkResult()

                        function checkResult() {
                            if (resultText.text == model.result) {
                                text.color = "#8080FF"
                                resultText.color = "#8080FF"
                                resultText.readOnly = true
                            }
                            else {
                                resultText.color = "#FF8080"
                            }
                        }
                    }

                    Text {
                        id: questionText
                        anchors.left: equalText.right
                        anchors.leftMargin: 8
                        width: contentWidth
                        height: parent.height
                        font.pixelSize: height * 0.8
                        color: !editButton.checked ? "white" : "yellow"
                        text: editButton.checked ? model.result : "?"
                        visible: editButton.checked || (!resultText.text && !resultText.cursorVisible)
                    }

                    Button {
                        anchors.left: questionText.right
                        anchors.leftMargin: 8
                        anchors.verticalCenter: parent.verticalCenter
                        width: height
                        height: parent.height * 0.8
                        style: Style.normalButton
                        visible: editButton.checked
                        iconSource: "qrc:/core/res/delete.svg"
                        tooltip: "Удалить"
                        onClicked: arithmetic.removeItem(index)
                    }
                }
            }

            ListView {
                id: listView
                anchors.fill: parent
                anchors.margins: 24
                model: arithmetic.items
                delegate: listItem
                interactive: false
                footer: Button {
                    width: Style.buttonSize
                    height: Style.buttonSize
                    style: Style.normalButton
                    visible: editButton.checked
                    iconSource: "qrc:/core/res/add.svg"
                    tooltip: "Добавить"
                    onClicked: arithmetic.addItem()
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
