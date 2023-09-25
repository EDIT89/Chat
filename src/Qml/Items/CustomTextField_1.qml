import QtQuick 2.12
import QtQuick.Controls 2.12

TextField
{
    id: textField
    placeholderTextColor: "#818c99"
    color: "black"
    height: 40
    selectByMouse: true
    selectedTextColor: "white"



    background: Rectangle {
        radius: 20
        color: "#d2d4d6"
        border.color: "mediumslateblue"
        border.width: 2
    }
}

