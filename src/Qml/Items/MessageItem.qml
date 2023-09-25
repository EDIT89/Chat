import QtQuick 2.12
import QtQuick.Controls 2.12

import QtQuick.Window 2.12
import QtQuick.Layouts 1.12
import QtQml 2.12

Rectangle
{
    id: messageBody

    property var messageText
    property var timestampText

    width: Math.min(messageLabel.implicitWidth + 30 + timestampBody.implicitWidth, 550)
    height: messageLabel.implicitHeight + timestampBody.implicitHeight + 25
    radius: 10
    color: "#cce4ff"

    Item
    {
        id: messageTextBody
        anchors.top: parent.top
        anchors.topMargin: 6
        anchors.left: parent.left
        anchors.leftMargin: 6
        anchors.right: parent.right
        anchors.rightMargin: 6
        anchors.bottom: timestampBody.top
        width: messageLabel.implicitWidth
        height: parent.height

        Text
        {
            id: messageLabel
            anchors.fill: parent
            text: messageText
            font.family: "Arial"
            font.pointSize: 11
            color: "Black"
            wrapMode: Text.Wrap
        }
    }

    Item
    {
        id: timestampBody
        anchors.right: parent.right
        anchors.rightMargin: 6
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 6
        width: timestampLabel.implicitWidth
        height: timestampLabel.implicitHeight

        Text
        {
            id: timestampLabel
            anchors.fill: parent
            text: timestampText
            color: "grey"
        }
    }
}

