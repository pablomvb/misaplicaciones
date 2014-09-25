import QtQuick 2.0

Item{

    Rectangle {
        width: main.width
        height: main.height-30
        color: "black"
    }

    Rectangle {
        id: rectangle1
        x: 0
        y: 6
        width: 262
        height: 184
        color: "#ffffff"

TextEdit {
    id: textEdit1
    x: 8
    y: 41
    width: 234
    height: 124
    text: qsTr("Text Editassssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssss")
    cursorVisible: true
    font.pixelSize: 12
    readOnly: false
}

    }

}

