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
    id: artithmetic

    Rectangle {
        anchors.fill: parent
        color: "#804020"
        radius: 16

        Rectangle {
            anchors.fill: parent
            anchors.margins: 16
            color: "#206020"
            radius: 12

            Component {
                id: listItem

                Item {
                    height: 40
                    width: text.width + Math.max(textEdit.width, question.width)

                    MouseArea {
                        anchors.fill: parent
                        cursorShape: Qt.ArrowCursor
                    }

                    Text {
                        id: text
                        width: contentWidth
                        height: parent.height
                        font.pixelSize: height * 0.8
                        color: "white"
                        text: model.left + " " + model.operation + " " + model.right + " = "
                    }

                    TextInput {
                        id: textEdit
                        anchors.left: text.right
                        width: question.width + contentWidth
                        height: parent.height
                        font.pixelSize: height * 0.8
                        color: "white"
                        validator: IntValidator {
                            bottom: -1000000
                            top: 1000000
                        }
                        onEditingFinished: checkResult()

                        function checkResult() {
                            if (textEdit.text == model.result) {
                                text.color = "#8080FF"
                                textEdit.color = "#8080FF"
                                textEdit.readOnly = true
                            }
                            else {
                                textEdit.color = "#FF8080"
                            }
                        }
                    }

                    Text {
                        id: question
                        anchors.left: textEdit.left
                        width: contentWidth
                        height: parent.height
                        font.pixelSize: height * 0.8
                        color: "white"
                        text: "?"
                        visible: !textEdit.text && !textEdit.cursorVisible
                    }
                }
            }

            ListView {
                anchors.fill: parent
                anchors.margins: 24
                model: artithmetic.items
                delegate: listItem
                interactive: false
            }
        }
    }
}
