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

        DialogRow
        {

            onDialogRowClicked:
            {
                dialogClicked(model.dialogId, model.dialogName)
                console.log("model.dialogId", model.dialogId)
            }
        }
    }
}
