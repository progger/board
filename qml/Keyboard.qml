import QtQuick 1.1
import "main.js" as Main

Rectangle {
    id: keyboard
    property int layout: 0
    property int shift: 0

    anchors.fill: parent
    color: "#C0C0C0"
    Column {
        id: keyboardColumn
        anchors.fill: parent
        Component.onCompleted: Main.main();
    }
}
