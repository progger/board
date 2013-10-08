import QtQuick 2.1
import QtQuick.Window 2.1
import QtQuick.Layouts 1.0
import board.core 2.0

Window {
    id: dialog
    signal closeApp
    signal save
    width: 400
    height: 80
    minimumWidth: width
    maximumWidth: width
    minimumHeight: height
    maximumHeight: height
    modality: Qt.ApplicationModal
    flags: Qt.Dialog | Qt.WindowCloseButtonHint
    title: "Имеются несохранённые изменения"

    Text {
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.top: parent.top
        anchors.bottom: buttonPanel.top
        horizontalAlignment: Text.AlignHCenter
        verticalAlignment: Text.AlignVCenter
        text: "Сохранить изменения?"
        font.pixelSize: height / 3
    }

    RowLayout {
        id: buttonPanel
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.bottom: parent.bottom
        anchors.margins: 8
        height: parent.height / 3
        spacing: 8

        Button {
            anchors.top: parent.top
            anchors.bottom: parent.bottom
            Layout.preferredWidth: 2
            Layout.fillWidth: true
            style: Style.normalButton
            text: "Закрыть без сохранения"
            onClicked: {
                closeApp()
                dialog.close()
            }
        }

        Button {
            anchors.top: parent.top
            anchors.bottom: parent.bottom
            Layout.preferredWidth: 1
            Layout.fillWidth: true
            style: Style.normalButton
            text: "Сохранить"
            onClicked: {
                save()
                dialog.close()
            }
        }

        Button {
            anchors.top: parent.top
            anchors.bottom: parent.bottom
            Layout.preferredWidth: 1
            Layout.fillWidth: true
            style: Style.normalButton
            text: "Отменить"
            onClicked: {
                dialog.close()
            }
        }
    }
}
