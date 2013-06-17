/*
 * Copyright (C) 2012 Michael Kulabuhov, Kemerovo, Russia.
 *
 * See the LICENSE file for terms of use.
 */

import QtQuick 2.0
import "qrc:/lib/cross/qml"

Rectangle {
    property real textSize: height * 0.05
    anchors.fill: parent
    color: "white"
    Keys.onPressed: Crossword.edit(event.text)

    CrossGrid {
        grid: Crossword.grid
        x: parent.width * 0.05
        y: parent.height * 0.05
        width: parent.width * 0.4
        height: parent.height * 0.65
        onCellClicked: Crossword.highlightCell(cell)
    }

    Rectangle {
        x: parent.width * 0.5
        y: parent.height * 0.05
        width: parent.width * 0.45
        height: parent.height * 0.65
        color: "#F0F0F0"
        radius: 12
        smooth: true

        ListView {
            anchors.fill: parent
            anchors.margins: 12
            model: Crossword.words
            spacing: 5
            clip: true
            currentIndex: Crossword.editingWordIndex
            delegate: Rectangle {
                width: parent.width
                height: text.height + textSize * 0.5
                radius: 8
                smooth: true
                color: getQuestionColor(modelData)

                Text {
                    id: text
                    color: "black"
                    anchors.left: parent.left
                    anchors.right: parent.right
                    anchors.verticalCenter: parent.verticalCenter
                    anchors.margins: 8
                    font.pixelSize: textSize
                    horizontalAlignment: Text.AlignJustify
                    wrapMode: Text.Wrap
                    text: modelData.question
                    smooth: true
                }

                MouseArea {
                    anchors.fill: parent
                    onClicked: Crossword.highlightWord(modelData)
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

    Component.onCompleted: {
        Core.keyboard = true;
        keyboard.layout = 1;
        keyboard.shift = 1;
    }
}
