import QtQuick 2.0

Item {
    id: menu
    state: "pgInicioC"
    signal clicked(string tab)

    Rectangle {
        width: main.width
        height: 30
        color: "black"
        anchors.bottom: parent.bottom
        anchors.bottomMargin: -(main.height)
        Text {
            id: txtInicio
            text: qsTr("Inicio")
            //text: "Inicio"
            y: 3
            color: "#5A5A5A"
            x: 7
            font.pixelSize: 20

            MouseArea{
                id: txtInicioMouseArea
                anchors.fill: parent
                hoverEnabled: true
                onEntered: {
                    txtInicio.color = "#12b0ff"
                }
                onExited: {
                    if(menu.state!="pgInicioC"){
                        txtInicio.color = "#5A5A5A"
                    } else {
                        txtInicio.color = "white"
                    }
                }
                onClicked: {
                    if(menu.state!="pgInicioC"){
                        console.log("Inicio click")
                        menu.clicked("pgInicio")
                    }
                    menu.state = "pgInicioC"
                }
            }
        }

        Text {
            id: txtDownManager
            text: "Descargas"
            color: "#5A5A5A"
            y: 3
            x: 62
            font.pixelSize: 20
            MouseArea{
                id: txtDescargasMouseArea
                anchors.fill: parent
                hoverEnabled: true
                onEntered: {
                    txtDownManager.color = "#12b0ff"
                }
                onExited: {
                    if(menu.state!="pgDescargasC"){
                        txtDownManager.color = "#5A5A5A"
                    } else {
                        txtDownManager.color = "white"
                    }
                }
                onClicked: {
                    if(menu.state!="pgDescargasC"){
                        console.log("Descargas click")
                        menu.clicked("pgDescargas")
                    }
                    menu.state = "pgDescargasC"
                }
            }
        }

        Text {
            id: txtPack
            text: "Empaquetar"
            color: "#5A5A5A"
            y: 3
            x: 164
            font.pixelSize: 20
            MouseArea{
                id: txtEmpaquetarMouseArea
                anchors.fill: parent
                hoverEnabled: true
                onEntered: {
                    txtPack.color = "#12b0ff"
                }
                onExited: {
                    if(menu.state!="pgEmpaquetarC"){
                        txtPack.color = "#5A5A5A"
                    } else {
                        txtPack.color = "white"
                    }
                }
                onClicked: {
                    if(menu.state!="pgEmpaquetarC"){
                        console.log("Empaquetar click")
                        menu.clicked("pgEmpaquetar")
                    }
                    menu.state = "pgEmpaquetarC"
                }
            }
        }

        Text {
            id: txtRenombrar
            text: "Renombrar"
            color: "#5A5A5A"
            y: 3
            x: 279
            font.pixelSize: 20
            MouseArea{
                id: txtRenombrarMouseArea
                anchors.fill: parent
                hoverEnabled: true
                onEntered: {
                    txtRenombrar.color = "#12b0ff"
                }
                onExited: {
                    if(menu.state!="pgRenombrarC"){
                        txtRenombrar.color = "#5A5A5A"
                    } else {
                        txtRenombrar.color = "white"
                    }
                }
                onClicked: {
                    if(menu.state!="pgRenombrarC"){
                        console.log("Renombrar click")
                        menu.clicked("pgRenombrar")
                    }
                    menu.state = "pgRenombrarC"
                }
            }
        }
    }
    states: [
        State {

            name: "pgInicioC"
            PropertyChanges {
                target: txtInicio
                color: "white"
            }
            PropertyChanges {
                target: txtDownManager
                color: "#5A5A5A"
            }
            PropertyChanges {
                target: txtPack
                color: "#5A5A5A"
            }
            PropertyChanges {
                target: txtRenombrar
                color: "#5A5A5A"
            }
        },
        State {
            name: "pgDescargasC"
            PropertyChanges {
                target: txtInicio
                color: "#5A5A5A"
            }
            PropertyChanges {
                target: txtDownManager
                color: "white"
            }
            PropertyChanges {
                target: txtPack
                color: "#5A5A5A"
            }
            PropertyChanges {
                target: txtRenombrar
                color: "#5A5A5A"
            }
        },
        State {
            name: "pgEmpaquetarC"
            PropertyChanges {
                target: txtInicio
                color: "#5A5A5A"
            }
            PropertyChanges {
                target: txtDownManager
                color: "#5A5A5A"
            }
            PropertyChanges {
                target: txtPack
                color: "white"
            }
            PropertyChanges {
                target: txtRenombrar
                color: "#5A5A5A"
            }
        },
        State {
            name: "pgRenombrarC"
            PropertyChanges {
                target: txtInicio
                color: "#5A5A5A"
            }
            PropertyChanges {
                target: txtDownManager
                color: "#5A5A5A"
            }
            PropertyChanges {
                target: txtPack
                color: "#5A5A5A"
            }
            PropertyChanges {
                target: txtRenombrar
                color: "white"
            }
        }
    ]
}
