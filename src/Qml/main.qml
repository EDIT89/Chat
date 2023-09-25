import QtQml 2.12
import QtQuick 2.12
import QtQuick.Window 2.12
import QtQuick.Controls 2.12
import "qrc:/"

Window {

    signal setPreviousPage(var currentItem)
    signal setPageToBeDeleted(var currentItem)

    width: 640
    height: 480
    visible: true
    title: qsTr("Chat")



    function initMainPage(page)
    {
        stackView.push(page)
    }

    function showNextPage(page)
    {
        console.log("setPreviousPage", stackView.currentItem.objectName)
        stackView.push(page)
    }

    function showPreviousPage(page)
    {
        console.log("setPageToBeDeleted", stackView.currentItem)
        setPageToBeDeleted(stackView.currentItem.objectName)
        stackView.push(page,StackView.PopTransition)
    }

    StackView
    {
        id: stackView
        anchors.fill: parent
    }
}
