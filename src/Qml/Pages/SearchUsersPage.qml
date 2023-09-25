import QtQuick 2.12
import QtQuick.Controls 2.12
import QtQuick.Window 2.10
import QtQuick.Dialogs 1.2
import QtQml 2.12

import "qrc:/Qml/Items/"

Page {
    id:searchUsersPage

    objectName:"qrc:/Qml/Pages/SearchUsersPage.qml"

    signal userNameClicked(var recipientId, var recipientName)
    signal backButton_Clicked

    property var searchUsersModel

    Rectangle
    {
        id:background
        anchors.fill: parent
    }


    SearchUsersPageHeader
    {
        id:header
        anchors.horizontalCenter: parent.horizontalCenter
        width: listView.width
        onBackButtonClicked:
        {
            backButton_Clicked()
        }
    }


    UserListView
    {
        id:listView
        height: parent.height
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.top: header.bottom
        model: searchUsersModel
    }

}
