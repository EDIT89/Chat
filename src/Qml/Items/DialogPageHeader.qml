import QtQuick 2.12
import QtQuick.Controls 2.12
import QtQuick.Layouts 1.12


Rectangle
{
    id:dialogPageHeader

    signal backButtonClicked
    signal searchUsersButtonClicked

    width: parent.width
    height: 50

    RowLayout
    {
        id: row
        anchors.fill: parent

        Button {
            id: backButton
            Layout.alignment: Qt.AlignLeft
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
            text: "Диалоги"
            color: "#818c99"
            Layout.alignment: Qt.AlignCenter
            font.pixelSize: 20
        }

        Button {
            id: searchUsersButton
            Layout.alignment: Qt.AlignRight
            icon.source: "qrc:/Qml/Images/free-icon-avatar-7609779.png"
            icon.color: "purple"
            onClicked: searchUsersButtonClicked()

            background: Rectangle{
                color: searchUsersButton.hovered ? "#f0f0f0":"white"
                implicitWidth: 10
                implicitHeight: 10
                radius: 10
            }
        }

    }
}
