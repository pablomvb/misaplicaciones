import QtQuick 2.3

Item{

    Rectangle {
        width: main.width
        height: main.height-30
        color: "white"

        Grid {
            property int sizegw: main.width-50
            property int sizegh: main.height-80
            id: gridMain
            x:25
            y:25
            width: sizegw
            height: sizegh
            columns: 2
            spacing: 20

            Rectangle{
                id:imgFondo
                width: 240
                height: 360
                color: "#8DF800"
                radius: 5
                Image {
                    x:8
                    y:10
                    id: imgPortada
                    source: ""
                    width: 230
                    height: 350

                }
            }

            Rectangle{
                //width: (main.width-50)-260
                //height: main.height-80
                width: gridMain.sizegw-260
                height: gridMain.sizegh
                color: "#8DF800"
                radius: 5

                Grid {
                    id: subGrid
                    columns: 2
                    rows: 5
                    spacing: 10
                    x:15
                    y:15
                    width: gridMain.sizegw-285
                    height: gridMain.sizegh-25
                    property int size_w_column_0: 145

                    Rectangle{
                        id: cell_0_0
                        width: subGrid.size_w_column_0
                        height: 33
                        color: "transparent"
                        Text {
                            id: name1
                            text: qsTr("Url")
                            verticalAlignment: Text.AlignVCenter
                            font.pixelSize: 15
                            anchors.verticalCenter: cell_0_0.verticalCenter
                        }

                    }

                    Rectangle{
                        id:cell_0_1
                        width: gridMain.sizegw-450
                        height: 33
                        color: "transparent"
                        Grid{
                            columns: 2
                            spacing: 10

                            LineInput{
                                //anchors.fill: txtUrlFondo

                            }

                            Button{
                                id: btnAnalizar
                                x:gridMain.sizegw-(450+btnAnalizar.sizew)
                                sizew: 80
                                sizeh: 33

                                onClickedBtn: console.log("emit Analizar: "+txtUrl.text)
                            }
                        }
                    }

                    Rectangle{
                        id: cell_1_0
                        width: subGrid.size_w_column_0
                        height: 33
                        color: "transparent"
                        Text {
                            id: name2
                            text: qsTr("Nombre")
                            verticalAlignment: Text.AlignVCenter
                            font.pixelSize: 15
                            anchors.verticalCenter: cell_1_0.verticalCenter
                        }
                    }

                    Rectangle{
                        id:cell_1_1
                        width: gridMain.sizegw-450
                        height: 33
                        radius: 3
                        border.width: 2
                        border.color: "#44D700"
                    }

                    Rectangle{
                        id: cell_2_0
                        width: subGrid.size_w_column_0
                        height: 33
                        color: "transparent"
                        Text {
                            id: name3
                            text: qsTr("Argumento ")
                            verticalAlignment: Text.AlignVCenter
                            font.pixelSize: 15
                            anchors.verticalCenter: cell_2_0.verticalCenter
                        }
                    }

                    Rectangle{
                        id:cell_2_1
                        width: gridMain.sizegw-450
                        height: gridMain.sizegh-202
                        radius: 3
                        border.width: 2
                        border.color: "#44D700"
                    }

                    Rectangle{
                        id: cell_3_0
                        width: subGrid.size_w_column_0
                        height: 33
                        color: "transparent"
                        Text {
                            id: name4
                            text: qsTr("Estado ")
                            verticalAlignment: Text.AlignVCenter
                            font.pixelSize: 15
                            anchors.verticalCenter: cell_3_0.verticalCenter
                        }
                    }

                    Rectangle{
                        id:cell_3_1
                        width: 300
                        height: 33
                        radius: 3
                        border.width: 2
                        border.color: "#44D700"
                    }

                    Rectangle{
                        id: cell_4_0
                        width: subGrid.size_w_column_0
                        height: 33
                        color: "transparent"
                        Text {
                            id: name5
                            text: qsTr("Numero de SubItem's")
                            verticalAlignment: Text.AlignVCenter
                            font.pixelSize: 15
                            anchors.verticalCenter: cell_4_0.verticalCenter
                        }
                    }

                    Rectangle{
                        id:cell_4_1
                        width: 200
                        height: 33
                        radius: 3
                        border.width: 2
                        border.color: "#44D700"
                    }
                }
            }
        }

        ProgresoBar{
            id: pbar
            x: main.width/2
            y: -((main.height-30)/2)
            opacity: 0
        }
    }

    states: [
        State {
            name: "analisisStart"
            PropertyChanges {
                target: pbar
                y: (main.height-30)/2
                opacity: 1
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
