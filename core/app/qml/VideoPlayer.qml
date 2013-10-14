/*
 * Copyright (C) 2012 Michael Kulabuhov, Kemerovo, Russia.
 *
 * See the LICENSE file for terms of use.
 */

import QtQuick 2.1
import QtQuick.Controls 1.0
import QtMultimedia 5.0
import board.core 2.0
import board.core.paint 2.0

VideoPlayer {
    id: videoPlayer

    Rectangle {
        anchors.fill: parent
        color: "#808080"
        radius: 8

        MediaPlayer {
            id: mediaPlayer
            source: videoPlayer.source
        }

        VideoOutput {
            anchors.left: parent.left
            anchors.top: parent.top
            anchors.right: parent.right
            anchors.bottom: panel.top
            anchors.margins: 8
            source: mediaPlayer
        }

        Item {
            id: panel
            anchors.left: parent.left
            anchors.right: parent.right
            anchors.bottom: parent.bottom
            anchors.margins: 8
            height: 30
            enabled: mediaPlayer.error === MediaPlayer.NoError

            Button {
                id: playButton
                anchors.left: parent.left
                anchors.top: parent.top
                anchors.bottom: parent.bottom
                width: height
                style: Style.roundButton
                iconSource: mediaPlayer.playbackState == MediaPlayer.PlayingState
                            ? "qrc:/core/res/pause.svg"
                            : "qrc:/core/res/play.svg"
                enabled: parent.enabled
                onClicked: playPause()

                function playPause() {
                    if (mediaPlayer.playbackState == MediaPlayer.PlayingState)
                        mediaPlayer.pause();
                    else
                        mediaPlayer.play();
                }
            }

            Button {
                id: stopButton
                anchors.left: playButton.right
                anchors.top: parent.top
                anchors.bottom: parent.bottom
                anchors.leftMargin: 4
                width: height
                style: Style.roundButton
                iconSource: "qrc:/core/res/stop.svg"
                enabled: parent.enabled
                onClicked: mediaPlayer.stop()
            }

            Item {
                id: volume
                anchors.left: stopButton.right
                anchors.top: parent.top
                anchors.bottom: parent.bottom
                anchors.leftMargin: 8
                width: height * 2

                Rectangle {
                    id: volumeLeft
                    anchors.left: parent.left
                    anchors.verticalCenter: parent.verticalCenter
                    width: parent.width * mediaPlayer.volume
                    height: parent.height / 3
                    color: "#40FF40"
                }

                Rectangle {
                    id: volumeRight
                    anchors.left: volumeLeft.right
                    anchors.right: parent.right
                    anchors.verticalCenter: parent.verticalCenter
                    height: parent.height / 3
                    color: "#804040"
                }

                Rectangle {
                    id: volumePos
                    x: volumeLeft.width - width / 2
                    anchors.top: parent.top
                    anchors.bottom: parent.bottom
                    width: 8
                    color: "#000080"
                }

                MouseArea {
                    anchors.fill: parent
                    hoverEnabled: true
                    onPressed: changeVolume(mouse)
                    onPositionChanged: changeVolume(mouse)

                    function changeVolume(mouse) {
                        if (mouse.buttons & Qt.LeftButton) {
                            mediaPlayer.volume = Math.min(Math.max(mouse.x / width, 0), 1)
                        }
                    }
                }
            }

            Item {
                id: position
                anchors.left: volume.right
                anchors.top: parent.top
                anchors.right: parent.right
                anchors.bottom: parent.bottom
                anchors.leftMargin: 16
                visible: mediaPlayer.seekable

                Rectangle {
                    id: positionLeft
                    anchors.left: parent.left
                    anchors.verticalCenter: parent.verticalCenter
                    width: parent.width * mediaPlayer.position / Math.max(mediaPlayer.duration, 1)
                    height: parent.height / 3
                    color: "#800000"
                }

                Rectangle {
                    id: positionRight
                    anchors.left: positionLeft.right
                    anchors.right: parent.right
                    anchors.verticalCenter: parent.verticalCenter
                    height: parent.height / 3
                    color: "#404040"
                }

                Rectangle {
                    id: positionPos
                    x: positionLeft.width - width / 2
                    anchors.top: parent.top
                    anchors.bottom: parent.bottom
                    width: 8
                    color: "#000080"
                }

                MouseArea {
                    anchors.fill: parent
                    hoverEnabled: true
                    onPressed: changePosition(mouse)
                    onPositionChanged: changePosition(mouse)

                    function changePosition(mouse) {
                        if (mouse.buttons & Qt.LeftButton) {
                            mediaPlayer.seek(Math.min(Math.max(mouse.x / width, 0), 1) * mediaPlayer.duration)
                        }
                    }
                }
            }
        }
    }

    onPlay: mediaPlayer.play()
}
