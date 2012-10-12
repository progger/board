/*
 * Copyright (C) 2012 Kulabuhov Michail, Kemerovo, Russia.
 *
 * See the LICENSE file for terms of use.
 */

import QtQuick 1.1

Rectangle {
    property real cellSize: Math.min(width * 0.4 / Crossword.width, height * 0.65 / Crossword.height)
    property real questionHeight: height * 0.65 / (Crossword.across().length + Crossword.down().length)
    z: 1
    anchors.fill: parent
    color: "white"

    Column {
        x: (parent.width * 0.5 - width) / 2
        y: parent.height * 0.05

        Repeater {
            model: Crossword.height

            Row {
                property int rowNum: index

                Repeater {
                    model: Crossword.width

                    Rectangle {
                        property int colNum: index
                        width: cellSize
                        height: cellSize
                        color: Crossword.viewGrid(colNum, rowNum) ? "white" : "black"
                        border.width: 1
                        border.color: "black"

                        Text {
                            color: "black"
                            anchors.centerIn: parent
                            font.pixelSize: parent.height / 2
                            text: Crossword.viewGrid(colNum, rowNum)
                            smooth: true
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
            model: Crossword.across()

            Item {
                width: parent.width
                height: questionHeight

                Rectangle {
                    anchors.fill: parent
                    anchors.margins: 4
                    color: "#E0E0E0"

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
                }
            }
        }

        Repeater {
            model: Crossword.down()

            Item {
                width: parent.width
                height: questionHeight

                Rectangle {
                    anchors.fill: parent
                    anchors.margins: 4
                    color: "#E0E0E0"

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
