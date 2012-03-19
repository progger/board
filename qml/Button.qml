import QtQuick 1.1

Rectangle {
    property real widthScale: 1
    property variant buttonText;

    width: keyboard.width / 15 * widthScale
    height: keyboard.height / 5
    color: keyboard.color
    Rectangle {
        anchors.fill: parent
        anchors.margins: 2
        radius: 4
        color: "#404040"
        Text {
            id: text
            text: buttonText[keyboard.layout][keyboard.shift]
            color: "#E0E0E0"
            anchors.centerIn: parent
            font.pixelSize: parent.height / 2
        }
    }
}
