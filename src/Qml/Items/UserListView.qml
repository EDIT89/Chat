import QtQuick 2.12
import QtQuick.Controls 2.12

ListView
{
    id: listView

    width: 550
    height: listView.height
    anchors.horizontalCenter: parent.horizontalCenter
    spacing: 0
    clip: true

    delegate: ItemDelegate
    {
        id:itemDelegate
        width: listView.width
        height: 70
        clip:true

        UserRow
        {
            onUserRowClicked:
            {
                userNameClicked(model.userId, model.login)
                console.log("model.userId", model.userId)
            }
        }
    }
}
