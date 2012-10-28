/*
 * Copyright (C) 2012 Kulabuhov Michail, Kemerovo, Russia.
 *
 * See the LICENSE file for terms of use.
 */

import QtQuick 1.1
import ":/lib/cross/qml"

Rectangle {
    property real questionWidth: width * 0.45
    property real questionHeight: height * 0.65 / Crossword.words.length
    anchors.fill: parent
    color: "white"
    Keys.onPressed: Crossword.edit(event.text)

    CrossGrid {
        grid: Crossword.grid
        x: parent.width * 0.05
        y: parent.height * 0.05
        width: parent.width * 0.4
        height: parent.height * 0.65
    }

    Column {
        x: parent.width * 0.5
        y: parent.height * 0.05

        Repeater {
            model: Crossword.words

            Item {
                width: questionWidth
                height: questionHeight

                Rectangle {
                    anchors.fill: parent
                    anchors.margins: 4
                    color: getQuestionColor(modelData)

                    Text {
                        color: "black"
                        anchors.fill: parent
                        anchors.margins: 4
                        font.pixelSize: parent.height * 0.4
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
                                ? "#C0FFC0"
                                : word.highlight
                                  ? "#A0A0FF"
                                  : "#E0E0E0";
                    }
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
