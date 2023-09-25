import QtQuick 2.12
import QtQuick.Controls 2.12
import QtQuick.Layouts 1.12


Rectangle
{
    id:searchUsersPageHeader

    signal backButtonClicked

    width: parent.width
    height: 50

    RowLayout
    {
        id: row
        anchors.fill: parent

        spacing: 150

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
            text: "Пользователи"
            color: "#818c99"
            font.pixelSize: 20
        }
    }
}
