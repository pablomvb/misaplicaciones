import QtQuick 2.2

Rectangle{
    width: 360
    height: 360
    id: window

    MouseArea {
        clip: false
        anchors.fill: parent
        onClicked: {
            Qt.quit();
        }
    }

    Text {
        text: "Hello World"
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 97
        anchors.right: parent.right
        anchors.rightMargin: 102
        horizontalAlignment: Text.AlignHCenter
    }

    MenuBar{}
}

