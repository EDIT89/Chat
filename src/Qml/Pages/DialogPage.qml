import QtQuick 2.12
import QtQuick.Controls 2.12
import QtQuick.Window 2.10
import QtQuick.Dialogs 1.2
import QtQml 2.12

import "qrc:/Qml/Items/"

Item {

    id:contactPage
    objectName:"qrc:/Qml/Pages/DialogPage.qml"

    signal dialogClicked(var dialogId, var dialogName)
    signal backButton_Clicked
    signal searchUsersButton_Clicked

    property var dialogModel

    Rectangle
    {
        id:background
        anchors.fill: parent
    }

    DialogPageHeader
    {
        id:dialogPageHeader
        anchors.horizontalCenter: parent.horizontalCenter
        width: listView.width
        onBackButtonClicked:
        {
            backButton_Clicked()
        }
        onSearchUsersButtonClicked:
        {
            searchUsersButton_Clicked()
        }
    }

    DialogListView
    {
        id:listView
        height: parent.height
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.top: dialogPageHeader.bottom
        model: dialogModel
    }
}
