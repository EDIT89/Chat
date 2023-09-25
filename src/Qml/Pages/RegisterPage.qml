import QtQuick 2.12
import QtQuick.Controls 2.12
import QtQuick.Layouts 1.12
import "qrc:/Qml/Items/"



Page {
    id:registerPage
    objectName:"qrc:/Qml/Pages/RegisterPage.qml"

    signal backButtonClicked
    signal registerButtonClicked(var reg_login,
                                 var reg_pass,
                                 var reg_pass_confirm)

    Rectangle
    {
        id: background
        color: "white"
        anchors.fill: parent
    }



    Text {
        id: title
        anchors.bottom: column.top
        anchors.bottomMargin: 30
        anchors.horizontalCenter: parent.horizontalCenter
        font.pointSize: 15

        text: qsTr("Придумайте логин и пароль")
        color: "#818c99"
    }

    ColumnLayout
    {
        id: column
        anchors.centerIn: parent
        spacing: 10


        CustomTextField_1
        {
            id:newLogin
            Layout.alignment: Qt.AlignCenter
            Layout.preferredWidth: 200
            Layout.preferredHeight: 40
            placeholderText: "Enter new login"
        }



        CustomTextField_1
        {
            id: newPassword
            Layout.alignment: Qt.AlignCenter
            Layout.preferredWidth: newLogin.width
            Layout.preferredHeight: newLogin.height
            echoMode:TextInput.Password
            placeholderText: "Enter password"
        }


        CustomTextField_1
        {
            id: confirmPassword
            Layout.alignment: Qt.AlignCenter
            Layout.preferredWidth: newLogin.width
            Layout.preferredHeight: newLogin.height
            echoMode:TextInput.Password
            placeholderText: "Confirm password"
        }



        CustomButton_1
        {
            id: signUp_btn
            text: "SIGN UP"
            Layout.alignment: Qt.AlignCenter
            Layout.preferredWidth: 100
            onClicked:
            {
                registerButtonClicked(newLogin.text,
                                      newPassword.text,
                                      confirmPassword.text);

            }
        }


        CustomButton_1
        {
            id: backButton
            text: "Back"
            Layout.alignment: Qt.AlignCenter
            Layout.preferredWidth: signUp_btn.width
            onClicked:
            {
                backButtonClicked()
            }
        }
    }
}
