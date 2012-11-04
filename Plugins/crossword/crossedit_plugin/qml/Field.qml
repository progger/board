/*
 * Copyright (C) 2012 Kulabuhov Michail, Kemerovo, Russia.
 *
 * See the LICENSE file for terms of use.
 */

import QtQuick 1.1
import ":/core/qml"
import ":/lib/cross/qml"

Rectangle {
    id: rootRect
    property real textSize: height * 0.04
    property real buttonSize: height * 0.06
    anchors.fill: parent
    color: "white"

    CrossGrid {
        grid: Crossedit.grid
        x: parent.width * 0.05
        y: parent.height * 0.05
        width: parent.width * 0.4
        height: parent.height * (Core.keyboard ? 0.65 : 0.9)
        gridColor: "#C0C0C0"
        onCellClicked: Crossedit.highlightCell(cell)
    }

    Row {
        x: parent.width * 0.5
        y: parent.height * 0.02
        spacing: 6

        Button {
            style: board.style.normalButton
            width: buttonSize
            height: buttonSize
            image: ":/plugin/crossedit/res/rotate.svg"
            enabled: Crossedit.editingWordIndex >= 0
            onClicked: Crossedit.rotateWord()
        }

        Rectangle {
            width: rootRect.width * 0.3
            height: buttonSize
            color: "#E0E0E0"
            border.width: 2
            border.color: "black"
            radius: 8
            smooth: true

            TextInput {
                id: nameInput
                color: "black"
                anchors.fill: parent
                anchors.margins: 6
                font.pixelSize: parent.height * 0.7
                text: Crossedit.crossName
                smooth: true
                onTextChanged: Crossedit.editCrossName(text)
            }

            Text {
                color: "#404040"
                anchors.centerIn: parent
                font.pixelSize: parent.height * 0.5
                font.italic: true
                text: "Название"
                smooth: true
                visible: !Crossedit.crossName && !nameInput.cursorVisible
            }
        }

        Button {
            style: board.style.normalButton
            width: buttonSize
            height: buttonSize
            enabled: Crossedit.crossName
            image: ":/core/res/save.svg"
            onClicked: Crossedit.save()
        }

        Button {
            style: board.style.normalButton
            width: buttonSize
            height: buttonSize
            image: ":/core/res/open.svg"
            toggled: Crossedit.fileListVisible
            onClicked: Crossedit.open()
        }
    }

    Rectangle {
        x: parent.width * 0.5
        y: parent.height * 0.1
        width: parent.width * 0.45
        height: parent.height * (Core.keyboard ? 0.60 : 0.85)
        color: "#F0F0F0"
        radius: 12
        smooth: true

        ListView {
            anchors.fill: parent
            anchors.margins: 12
            model: Crossedit.words
            spacing: 5
            clip: true
            currentIndex: Crossedit.editingWordIndex
            delegate: Rectangle {
                property variant md: modelData
                width: parent.width
                height: wordRect.height + questionRect.height + 18
                radius: 8
                smooth: true
                color: getQuestionColor(modelData)

                Rectangle {
                    id: wordRect
                    anchors.left: parent.left
                    anchors.right: parent.right
                    anchors.top: parent.top
                    anchors.margins: 6
                    height: wordInput.height + textSize * 0.5
                    radius: 6
                    smooth: true
                    color: "#C0C0C0"

                    TextInput {
                        id: wordInput
                        color: "black"
                        anchors.left: parent.left
                        anchors.right: parent.right
                        anchors.verticalCenter: parent.verticalCenter
                        anchors.margins: 6
                        font.pixelSize: textSize
                        horizontalAlignment: Text.AlignJustify
                        text: modelData.word
                        onTextChanged: Crossedit.editWord(modelData, text)
                        smooth: true
                    }

                    Text {
                        color: "#404040"
                        anchors.centerIn: parent
                        font.pixelSize: textSize * 0.8
                        font.italic: true
                        text: "Слово"
                        smooth: true
                        visible: !modelData.word && !wordInput.cursorVisible
                    }
                }

                Rectangle {
                    id: questionRect
                    anchors.left: parent.left
                    anchors.right: parent.right
                    anchors.top: wordRect.bottom
                    anchors.margins: 6
                    height: questionEdit.height + textSize * 0.5
                    radius: 6
                    smooth: true
                    color: "#A0A0A0"

                    TextEdit {
                        id: questionEdit
                        color: "black"
                        anchors.left: parent.left
                        anchors.right: parent.right
                        anchors.verticalCenter: parent.verticalCenter
                        anchors.margins: 6
                        font.pixelSize: textSize
                        horizontalAlignment: Text.AlignJustify
                        text: modelData.question
                        onTextChanged: modelData.question = text
                        smooth: true
                        wrapMode: TextEdit.WordWrap
                    }

                    Text {
                        color: "#404040"
                        anchors.centerIn: parent
                        font.pixelSize: textSize * 0.8
                        font.italic: true
                        text: "Вопрос"
                        smooth: true
                        visible: !modelData.question && !questionEdit.cursorVisible
                    }
                }

                function getQuestionColor(word) {
                    return word.accepted
                            ? "#C0F0C0"
                            : word.highlight
                              ? "#A0A0FF"
                              : "#D0D0D0";
                }
            }
        }
    }

    Rectangle {
        z: 1
        x: parent.width * 0.5
        y: parent.height * 0.1
        width: parent.width * 0.45
        height: parent.height * (Core.keyboard ? 0.60 : 0.85)
        color: "#F0F0F0"
        radius: 12
        smooth: true
        opacity: Crossedit.fileListVisible

        Behavior on opacity {
            NumberAnimation { duration: 500 }
        }

        ListView {
            anchors.fill: parent
            anchors.margins: 12
            model: Crossedit.fileList
            spacing: 5
            clip: true
            delegate: Rectangle {
                width: parent.width
                height: textSize * 1.5
                color: "#C0C0C0"
                radius: 6
                smooth: true

                Text {
                    anchors.fill: parent
                    anchors.margins: 4
                    font.pixelSize: textSize
                    text: modelData
                    smooth: true
                }

                MouseArea {
                    anchors.fill: parent
                    onClicked: Crossedit.openFile(modelData)
                }
            }
        }
    }
}
