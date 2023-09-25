import QtQuick 2.12
import QtQuick.Controls 2.12
import QtQuick.Layouts 1.12


Rectangle
{
    id:conversationPageHeader

    signal backButtonClicked
    property var dialogName

    width: parent.width
    height: 40


    Button {
        id: backButton
        anchors.left: parent.left
        anchors.verticalCenter: parent.verticalCenter
        icon.source: "qrc:/Qml/Images/free-icon-back-4562793.png"
        icon.color: "purple"
        onClicked: backButtonClicked()

        background: Rectangle{
            color: backButton.hovered ? "#f0f0f0":"white"
            implicitWidth: 10
            implicitHeight: 10
            radius: 10
        }
    }


    Text
    {
        id: headerText
        anchors.horizontalCenter: conversationPageHeader.horizontalCenter
        anchors.verticalCenter: parent.verticalCenter
        text: dialogName
        color: "#818c99"
        font.pixelSize: 20
    }

}
