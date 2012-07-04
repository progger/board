// import QtQuick 1.0 // to target S60 5th Edition or Maemo 5
import QtQuick 1.1

Item {

    Rectangle {
        anchors.fill: parent
        color: "#404040"
        opacity: 0.5
    }

    GridView {
        id: pluginInfoGrid
        property real buttonWidth: 128
        property real imageHeigth: 128
        property real textHeight: 32
        property real buttonHeight: imageHeigth + textHeight
        anchors.fill: parent
        anchors.margins: 8
        cellWidth: buttonWidth + 8
        cellHeight: buttonHeight + 8
        model: RootPluginInfo.children
        delegate: Item {
            id: gridDelegate
            width: pluginInfoGrid.buttonWidth
            height: pluginInfoGrid.buttonHeight

            MouseArea {
                id: mouseArea
                anchors.fill: parent
                hoverEnabled: true
                onClicked: onClick(modelData)

                function onClick(modelData) {
                    if (modelData.isDir)
                        pluginInfoGrid.model = modelData.children;
                    else
                        Core.selectPlugin(modelData);
                }
            }

            Rectangle {
                anchors.fill: parent
                color: mouseArea.containsMouse ? "#E0E0E0" : "#808080"
                radius: 8
                smooth: true
                opacity: 0.5
            }

            Image {
                id: buttonImage
                anchors.left: parent.left
                anchors.right: parent.right
                anchors.top: parent.top
                height: pluginInfoGrid.imageHeigth
                source: modelData.image
                smooth: true
            }

            Item {
                id: buttonText
                anchors.left: parent.left
                anchors.right: parent.right
                anchors.top: buttonImage.bottom
                anchors.bottom: parent.bottom

                Text {
                    anchors.centerIn: parent
                    font.pixelSize: parent.height * 0.7
                    text: modelData.objectName
                    smooth: true
                }
            }
        }
    }
}
