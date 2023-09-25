import QtQuick 2.12
import QtGraphicalEffects 1.0

Item {

    id:roundImage

    property string avatarImageSource

    width: 50
    height: 50



    Image {
        id: avatarImage
        width: parent.width
        height: parent.height
        source: avatarImageSource
        visible: false
    }



    Rectangle
    {
        id:mask
        width: parent.width
        height: parent.height
        radius: width * 0.5
        visible: false
    }



    OpacityMask
    {
        anchors.fill: avatarImage
        source: avatarImage
        maskSource: mask
    }
}
