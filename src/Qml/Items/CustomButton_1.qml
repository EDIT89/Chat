import QtQuick 2.12
import QtQuick.Controls 2.12

Button {
    id:customButton
    text: "button"

    highlighted: true


    contentItem: Text {
            text: customButton.text
            font: customButton.font
            color: "white"
            horizontalAlignment: Text.AlignHCenter
            verticalAlignment: Text.AlignVCenter
            elide: Text.ElideRight
        }

    background: Rectangle {
        implicitHeight: 40
        radius: 5
        color: customButton.down ? "#9483f1" : "mediumslateblue"
    }

}
