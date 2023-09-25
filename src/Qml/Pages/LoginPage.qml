import QtQuick 2.12
import QtQuick.Controls 2.12

import QtQuick.Window 2.12
import QtQuick.Layouts 1.12
import QtQml 2.12
import "qrc:/Qml/Items/"

Page {

    id:loginPage

    objectName: "qrc:/Qml/Pages/LoginPage.qml"
    signal loginButtonClicked(var login, var pass)
    signal signUpButtonClicked

    property int centerEnterKey: 16777220
    property int rightEnterKey: 16777221


    focus: true
    Keys.onPressed:
    {
        if(event.key === centerEnterKey || event.key === rightEnterKey )
        {
            loginPage.loginButtonClicked(loginTextField.text, passwordTextField.text)
            event.accepted = true
        }
    }


    background:Rectangle
    {
        id: background
        anchors.fill: parent
        color: "white"
    }





    Text {
        id: title
        anchors.bottom: column.top
        anchors.bottomMargin: 30
        anchors.horizontalCenter: parent.horizontalCenter
        font.pointSize: 15

        text: qsTr("Введите логин и пароль")
        color: "#818c99"
    }

    ColumnLayout
    {
        id: column
        anchors.centerIn: parent
        spacing: 10


        CustomTextField_1
        {
            id:loginTextField
            Layout.alignment: Qt.AlignCenter
            Layout.preferredWidth: 200
            Layout.preferredHeight: 40
            placeholderText: "Enter Login"
        }



        CustomTextField_1
        {
            id: passwordTextField
            Layout.alignment: Qt.AlignCenter
            Layout.preferredWidth: loginTextField.width
            Layout.preferredHeight: loginTextField.height
            echoMode:TextInput.Password
            placeholderText: "Enter password"
        }



        CustomButton_1
        {
            id: signIn_btn
            text: "SIGN IN"
            Layout.alignment: Qt.AlignCenter
            Layout.preferredWidth: 100
            onClicked:
            {
                if(loginTextField.length > 0 && passwordTextField.length > 0)
                {
                    loginPage.loginButtonClicked(loginTextField.text,
                                                 passwordTextField.text)
                    loginTextField.clear()
                    passwordTextField.clear()
                }
            }
        }


        CustomButton_1
        {
            id: signUp_btn
            text: "SIGN UP"
            Layout.alignment: Qt.AlignCenter
            Layout.preferredWidth: signIn_btn.width
            onClicked:
            {
                signUpButtonClicked()
            }
        }
    }
}
