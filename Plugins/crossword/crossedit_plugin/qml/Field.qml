/*
 * Copyright (C) 2012 Kulabuhov Michail, Kemerovo, Russia.
 *
 * See the LICENSE file for terms of use.
 */

import QtQuick 1.1
import ":/core/qml"
import ":/lib/cross/qml"

Rectangle {
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

    Button {
        style: board.style.normalButton
        x: parent.width * 0.5
        y: parent.height * 0.02
        width: buttonSize
        height: buttonSize
        onClicked: Crossedit.rotateWord()
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
}
