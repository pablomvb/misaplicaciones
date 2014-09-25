import QtQuick 2.3

Item{
    id: guiaplicacion
    state: "pgInicio"

    Xtractor{
        id: xtractor
        opacity: 0
        x:0
    }

    Descargas{
        id: descargas
        opacity: 0
        x: main.width
    }

    Empaquetar{
        id: empaquetar
        opacity: 0
        x: main.width
    }

    Renombrar{
        id: renombrar
        opacity: 0
        x: main.width
    }

    MenuBar{
        id: menuBotonBar

        onClicked: {
            guiaplicacion.state = tab
            console.log("estado : "+tab)
        }
    }

    states: [
        State {
            name: "pgInicio"
            PropertyChanges {
                target: xtractor
                opacity: 1
                x:0
            }
        },
        State {
            name: "pgDescargas"
            PropertyChanges {
                target: descargas
                opacity: 1
                x:0
            }
            PropertyChanges {
                target: xtractor
                opacity: 0
                x: -(main.width)
            }
        },
        State {
            name: "pgEmpaquetar"
            PropertyChanges {
                target: empaquetar
                opacity: 1
                x: 0
            }
            PropertyChanges {
                target: xtractor
                opacity: 0
                x: -(main.width)
            }
            PropertyChanges {
                target: descargas
                opacity: 0
                x: -(main.width)
            }
        },
        State {
            name: "pgRenombrar"
            PropertyChanges {
                target: renombrar
                opacity: 1
                x: 0
            }
            PropertyChanges {
                target: xtractor
                opacity: 0
                x: -(main.width)
            }
            PropertyChanges {
                target: descargas
                opacity: 0
                x: -(main.width)
            }
            PropertyChanges{
                target: empaquetar
                opacity: 0
                x: -(main.width)
            }
        }
    ]
    transitions: [
        Transition {
            NumberAnimation {
                properties: "x"
                easing.type: Easing.OutQuart
                duration: 370
            }
            NumberAnimation{
                properties: "opacity"
                easing.type: Easing.InQuad
                duration: 370
            }
        }
    ]
}

//NumberAnimation { properties: "x,y"; easing.type: Easing.OutQuart; duration: 1000 }
//NumberAnimation { properties: "opacity"; easing.type: Easing.InQuad; duration: 500 }
