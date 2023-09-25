import QtQuick 2.12
import QtQuick.Layouts 1.12
import QtQuick.Controls 2.12
import "qrc:/Qml/Items/"


Page {
    id: root
    objectName:"qrc:/Qml/Pages/ConversationPage.qml"

    signal backButton_Clicked
    signal sendMessageButtonClicked(var dialogId1,
                                    var currentUserId,
                                    var recipientId,
                                    var message)

    signal activeFocusChanged(var focus)

    property var conversationModel
    property var dialog_Name
    property var dialogId1
    property var currentUserId
    property var recipientId

    function moveToMessage()
    {
        listView.positionViewAtBeginning()
    }

    ConversationPageHeader
    {
        id:header
        anchors.horizontalCenter: parent.horizontalCenter
        dialogName: dialog_Name
        width: listView.width
        onBackButtonClicked:
        {
            backButton_Clicked()
        }
    }

    ColumnLayout
    {
        id:column
        anchors.top: header.bottom
        anchors.horizontalCenter: parent.horizontalCenter
        width:550
        height: parent.height - header.height
        ChatListView
        {
            id:listView
            Layout.fillWidth: true
            Layout.fillHeight: true
            model: conversationModel
        }


        ConversationTextField
        {
            id: conversationTextField
            Layout.fillWidth: true
            onSendButtonClicked:
            {
                sendMessageButtonClicked(root.dialogId1,
                                         root.currentUserId,
                                         root.recipientId,
                                         conversationTextField.messageFieldText)

            }
        }
    }

}
