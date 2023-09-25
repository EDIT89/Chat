import QtQuick 2.12
import QtQuick.Controls 2.12

import QtQuick.Window 2.12
import QtQuick.Layouts 1.12
import QtQml 2.12

Item
{
    id: contactItem
    //signals to QML
    signal dialogRowClicked

    property string dialogName_Text
    property string lastMessage_Text
    property string lastMessageDateTime_Text
    property string status_Circle

    Rectangle
    {
        id: parentRect
        width: 550
        height: 70


        RoundImage
        {
            id:avatar
            x:10
            anchors.verticalCenter: parent.verticalCenter
            avatarImageSource: "qrc:/Qml/Images/defaultAvatar.png"
        }

        Text
        {
            id:dialogNameText
            anchors.left: avatar.right
            anchors.leftMargin: 10
            y: 12
            text: dialogName
            font.family: "Arial"
            font.pointSize: 11
            color: "Black"
        }

        Text
        {
            id: lastMessageText
            text: lastMessage
            anchors.top: dialogNameText.bottom
            anchors.topMargin: 9
            anchors.left: avatar.right
            anchors.leftMargin: 10
            font.family: "Arial"
            font.pointSize: 11
            color: "grey"
        }

        Text
        {
            id: lastMessageDateTimeText
            text: lastMessageTime
            anchors.verticalCenter: lastMessageText.verticalCenter
            x: 500
            font.family: "Arial"
            font.pointSize: 9
            color: "grey"
        }

        Rectangle
        {
            id: statusCircle
            width: 8
            height: 8
            radius: 4
            color: "green"
            anchors.left: dialogNameText.right
            anchors.leftMargin: 5
            anchors.verticalCenter: dialogNameText.verticalCenter
            visible: userStatus
        }

        Rectangle
        {
            id: bottomLine
            color: "#dce1e6"
            x: 60
            width: 490
            height: 1
            y:69

        }

        MouseArea
        {
            anchors.fill: parent
            hoverEnabled: true
            onEntered: parent.color = "#f5f6f8"
            onExited: parent.color = "white"
            onClicked:
            {
                console.log(statusCircle.visible)
                dialogRowClicked()
            }
        }
    }
}
