import QtQuick 2.12
import QtQuick.Controls 2.12
import QtQuick.Layouts 1.12

ListView
{
    id:listView

    property var messageItemText
    property var messageItemTimestampText

    width: 550
    height: listView.height
    verticalLayoutDirection: ListView.BottomToTop
    spacing: 4
    clip: true

    delegate:ItemDelegate
    {
        id: messageDelegate
        width: messageItem.width
        height: messageItem.height
        clip: true

        anchors.right:
        {
            if(rightSide)
                parent.right
        }
        anchors.left:
        {
            if(!rightSide)
                parent.left
        }

        anchors.rightMargin: 8
        anchors.leftMargin: 8
        MessageItem
        {
            id: messageItem
            messageText: incommingData
            timestampText: timestamp
        }
    }

    ScrollBar.vertical: ScrollBar {
        width: 8
    }
}
