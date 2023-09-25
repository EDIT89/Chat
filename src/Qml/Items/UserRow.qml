import QtQuick 2.12
import QtQuick.Controls 2.12

import QtQuick.Window 2.12
import QtQuick.Layouts 1.12
import QtQml 2.12

Item
{
    id: contactItem
    //signals to QML
    signal userRowClicked

    property string userName_Text
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
            id:userNameText
            anchors.left: avatar.right
            anchors.leftMargin: 10
            y: 12
            text: login
            font.family: "Arial"
            font.pointSize: 11
            color: "Black"
        }

        Rectangle
        {
            id: statusCircle
            width: 8
            height: 8
            radius: 4
            color: "green"
            anchors.left: text.right
            anchors.leftMargin: 5
            anchors.verticalCenter: text.verticalCenter
            visible: status_Circle
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
                userRowClicked()
            }
        }
    }
}
