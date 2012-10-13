/*
 * Copyright (C) 2012 Kulabuhov Michail, Kemerovo, Russia.
 *
 * See the LICENSE file for terms of use.
 */

import QtQuick 1.1

Rectangle {
    property real cellSize: Math.min(width * 0.4 / Crossword.width, height * 0.65 / Crossword.height)
    property real questionHeight: height * 0.65 / Crossword.words().length
    z: 1
    anchors.fill: parent
    color: "white"
    Keys.onPressed: Crossword.edit(event.text)

    Column {
        x: (parent.width * 0.5 - width) / 2
        y: parent.height * 0.05

        Repeater {
            model: Crossword.rows()

            Row {

                Repeater {
                    model: modelData.cells()

                    Rectangle {
                        width: cellSize
                        height: cellSize
                        color: getCellColor(modelData)
                        border.width: modelData.type() > 0
                        border.color: "black"

                        Text {
                            color: "black"
                            anchors.centerIn: parent
                            font.pixelSize: parent.height / 2
                            text: modelData.letter
                            smooth: true
                        }

                        MouseArea {
                            anchors.fill: parent
                            onClicked: Crossword.highlightCell(modelData)
                        }

                        function getCellColor(cell) {
                            switch (cell.type())
                            {
                            case 0:
                                return "transparent";
                            case 1:
                                return "black";
                            case 2:
                                return cell.accepted
                                        ? "#C0FFC0"
                                        : cell.editing
                                          ? "#FFA0A0"
                                          : cell.highlight
                                            ? "#A0A0FF"
                                            : "white";
                            }
                        }
                    }
                }
            }
        }
    }

    Column {
        x: parent.width * 0.5
        y: parent.height * 0.05
        width: parent.width * 0.45

        Repeater {
            model: Crossword.words()

            Item {
                width: parent.width
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
                        text: modelData.question()
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
