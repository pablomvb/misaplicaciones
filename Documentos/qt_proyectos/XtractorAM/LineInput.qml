import QtQuick 2.3

Item {
    id: lineIn

    property int size_w : gridMain.sizegw-(460+btnAnalizar.sizew)
    property int size_h: 15

    Rectangle{
        id: txtUrlFondo
        width: size_w
        height: 33
        radius: 3
        border.width: 2
        border.color: "#44D700"
        anchors.top: lineIn.top
        anchors.bottom: lineIn.bottom
        anchors.left: lineIn.left
        anchors.right: lineIn.right

        TextInput{
            id:txtUrl
            font.pixelSize: 15
            //verticalAlignment: Text.AlignVCenter
            //width: main.width-50-(460+btnAnalizar.sizew)-18
            width: size_w-18
            color: "red"
            height: size_h
            text: ""
            cursorVisible: true
            //anchors.verticalCenter: txtUrlFondo.verticalCenter
            //anchors.horizontalCenter: txtUrlFondo.horizontalCenter
            anchors.fill: txtUrlFondo
            anchors.margins: 8
            readOnly: false
            smooth: true
            selectByMouse: true
            focus: true
        }
    }
}
