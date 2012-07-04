// import QtQuick 1.0 // to target S60 5th Edition or Maemo 5
import QtQuick 1.1

Item {
    property real buttonWidth: 128
    property real imageHeigth: 128
    property real textHeight: 32
    property real buttonHeight: imageHeigth + textHeight
    property real buttonMargin: 8
    property variant currenPluginInfo: RootPluginInfo

    Rectangle {
        anchors.fill: parent
        color: "#404040"
        opacity: 0.5
    }

   Rectangle  {
        id: backButton
        x: buttonMargin
        y: buttonMargin
        width: buttonWidth
        height: imageHeigth
        color: backButtonMouseArea.containsMouse ? "#E0E0E0" : "#808080"
        radius: 8
        smooth: true
        opacity: 0.5
        visible: currenPluginInfo != RootPluginInfo

        Image {
            anchors.fill: parent
            source: "qrc:/core/res/back.svg"
        }

        MouseArea {
            id: backButtonMouseArea
            anchors.fill: parent
            hoverEnabled: true
            onClicked: currenPluginInfo = currenPluginInfo.parent
        }
    }

    GridView {
        id: pluginInfoGrid
        anchors.left: backButton.right
        anchors.right: parent.right
        anchors.top: parent.top
        anchors.bottom: parent.bottom
        anchors.margins: buttonMargin
        cellWidth: buttonWidth + buttonMargin
        cellHeight: buttonHeight + buttonMargin
        model: currenPluginInfo.children
        delegate: Item {
            id: gridDelegate
            width: buttonWidth
            height: buttonHeight

            MouseArea {
                id: mouseArea
                anchors.fill: parent
                hoverEnabled: true
                onClicked: onClick(modelData)

                function onClick(modelData) {
                    if (modelData.isDir)
                        currenPluginInfo = modelData;
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
                height: imageHeigth
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
