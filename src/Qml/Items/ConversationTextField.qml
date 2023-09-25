import QtQuick 2.12
import QtQuick.Controls 2.12
import QtQuick.Layouts 1.12



Pane {
    id: pane

    signal sendButtonClicked

    property var messageFieldText

    Layout.fillWidth: true
    background: Rectangle
    {
        anchors.verticalCenter:parent.verticalCenter
        width:parent.width
        height: messageField.height + 18
        radius: 5
        color:"#efefef"

    }

    RowLayout {
        width: parent.width

        TextArea {
            id: messageField
            Layout.fillWidth: true
            color: "black"
            font.family: "Arial"
            font.pointSize: 11
            placeholderText: qsTr("Compose message")
            wrapMode: TextArea.Wrap
            selectByMouse: true
            selectedTextColor: "white"
        }

        RoundButton {
            id: sendButton
            background:
            {
                icon.source = "qrc:/Qml/Images/free-icon-send-data.png"
                icon.color = "purple"
            }

            enabled: messageField.length > 0
            onClicked:
            {
                messageFieldText = messageField.text
                messageField.clear()
                sendButtonClicked()
            }
        }
    }
}

