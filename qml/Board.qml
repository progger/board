import QtQuick 1.0

Rectangle {
    id: board
    property Style style: Style {}

    width: 400
    height: 300

    Rectangle {
        id: toolBarArea
        anchors.top: parent.top
        anchors.left: parent.left
        anchors.right: parent.right
        height: 32
        color: "red"

        MouseArea {
            anchors.fill: parent
            onClicked: {
                Qt.quit();
            }
        }

    }

    Rectangle {
        id: centerArea
        anchors.top: toolBarArea.bottom
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.bottom: parent.bottom

        Rectangle {
            id: modeBarArea
            anchors.top: parent.top
            anchors.bottom: parent.bottom
            anchors.left: parent.left
            width: 44

            ModeBar {
                style: board.style
                anchors.fill: parent
            }
        }

        Rectangle {
            id: drawArea
            anchors.top: parent.top
            anchors.bottom: parent.bottom
            anchors.left: modeBarArea.right
            anchors.right: parent.right

            Draw {
                anchors.fill: parent
            }
        }
    }

    Keyboard {
        id: keyboard
        style: board.style
        anchors.bottom: parent.bottom
        anchors.horizontalCenter: parent.horizontalCenter
        height: board.height / 4
        //visible: Core.keyboard
        opacity: Core.keyboard
        Behavior on opacity {
            NumberAnimation { duration: 500 }
        }
    }
}
