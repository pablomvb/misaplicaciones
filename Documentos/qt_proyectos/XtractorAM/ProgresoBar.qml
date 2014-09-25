import QtQuick 2.0

Item{
    id: progressBarWidget
    state: "c1"

    function cambiarEstado(){
        console.log("clock signal")
        if(progressBarWidget.state=="c1"){
            progressBarWidget.state = "c2"
            console.log("c2")
        } else if(progressBarWidget.state=="c2"){
            progressBarWidget.state = "c3"
            console.log("c3")
        } else if(progressBarWidget.state=="c3"){
            progressBarWidget.state = "c4"
            console.log("c4")
        } else if(progressBarWidget.state=="c4"){
            progressBarWidget.state = "c1"
            console.log("c5")
        }
    }

    function iniciar(iniciarTimer){
        if(iniciarTimer===0){
            progressBarTimer.stop()
        } else if(iniciarTimer===1){
            progressBarTimer.start()
        }
    }

    Rectangle{
        id:fondoProgressBar
        width: main.width
        height: main.height-30
        color: "#33000000"
        anchors.centerIn: parent

        Rectangle{
            width: 400
            height: 200
            anchors.centerIn: parent
            color: "white"
            radius: 10

            Text {
                id: txtDebugProgreso
                text: "Espere..."
                horizontalAlignment: Text.AlignHCenter
                anchors.horizontalCenter: parent.horizontalCenter
                y:140
                font.pixelSize: 20
            }

            Rectangle{
                id:r1
                width: 60
                height: 60
                radius: 30
                x:50
                y:40
                border.width: 2
                border.color: "#d6f0ff"
                color: "#edf9ff"
            }

            Rectangle{
                id:r2
                width: 60
                height: 60
                radius: 30
                x:130
                y:40
                border.width: 2
                border.color: "#d6f0ff"
                color: "#edf9ff"
            }

            Rectangle{
                id:r3
                width: 60
                height: 60
                radius: 30
                x: 210
                y:40
                border.width: 2
                border.color: "#d6f0ff"
                color: "#edf9ff"
            }

            Rectangle{
                id:r4
                width: 60
                height: 60
                radius: 30
                x:290
                y:40
                border.width: 2
                border.color: "#d6f0ff"
                color: "#edf9ff"
            }

            Rectangle{
                id:rb1
                width: 60
                height: 60
                radius: 30
                x:50
                y:40
                border.width: 2
                border.color: "#76ceff"
                color: "#9fe2ff"
                opacity: 0
            }

            Rectangle{
                id:rb2
                width: 60
                height: 60
                radius: 30
                x:130
                y:40
                border.width: 2
                border.color: "#76ceff"
                color: "#9fe2ff"
                opacity: 0
            }

            Rectangle{
                id:rb3
                width: 60
                height: 60
                radius: 30
                x: 210
                y:40
                border.width: 2
                border.color: "#76ceff"
                color: "#9fe2ff"
                opacity: 0
            }

            Rectangle{
                id:rb4
                width: 60
                height: 60
                radius: 30
                x:290
                y:40
                border.width: 2
                border.color: "#76ceff"
                color: "#9fe2ff"
                opacity: 0
            }
        }
    }

    states: [
        State {
            name: "c1"
            PropertyChanges {
                target: rb1
                opacity: 1
            }
        },
        State {
            name: "c2"
            PropertyChanges {
                target: rb2
                opacity: 1
            }
            PropertyChanges {
                target: rb1
                opacity: 0
            }
        },
        State {
            name: "c3"
            PropertyChanges {
                target: rb3
                opacity: 1
            }
            PropertyChanges {
                target: rb1
                opacity: 0
            }
            PropertyChanges {
                target: rb2
                opacity: 0
            }
        },
        State {
            name: "c4"
            PropertyChanges {
                target: rb4
                opacity: 1
            }
            PropertyChanges {
                target: rb1
                opacity: 0
            }
            PropertyChanges {
                target: rb2
                opacity: 0
            }
            PropertyChanges {
                target: rb3
                opacity: 0
            }
        }
    ]

    transitions: [
        Transition {
            NumberAnimation {
                properties: "opacity"
                easing.type: Easing.OutQuad
                duration: 250
            }
        }
    ]

    Timer{
        id: progressBarTimer
        interval: 750; running: false; repeat: true;
        onTriggered: parent.cambiarEstado()
    }

}
