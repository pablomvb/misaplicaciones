import QtQuick 2.0

Item{
    id: btn
    property int sizew: 80
    property int sizeh: 33

    signal clickedBtn()

    Rectangle {
        id: btnFondo
        width: sizew
        height: sizeh
        color: "green"
        radius: 3
        border.width: 2
        border.color: "#44D700"
        Text {
            id: txtBtn
            text: qsTr("Analizar")
            color: "white"
            anchors.verticalCenter: btnFondo.verticalCenter
            anchors.horizontalCenter: btnFondo.horizontalCenter
            font.pixelSize: 15
        }

        MouseArea{
            id: btnFondoMouseArea
            anchors.fill: parent
            hoverEnabled: true
            onEntered: {
                btnFondo.color = "#35A600"
            }
            onExited: {
                btnFondo.color = "green"
            }
            onClicked: {
                //btnFondo.color = "green"
                btn.clickedBtn()
            }
        }
    }
}
