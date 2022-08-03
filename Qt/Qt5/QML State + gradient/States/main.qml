import QtQuick 2.12
import QtQuick.Window 2.12
import QtQuick.Controls 2.0
import QtQuick.Layouts 1.0

Window {
    width: 640
    height: 480
    visible: true
    title: qsTr("State Example")

    Column{
        spacing: 15
        anchors.centerIn: parent
        Button{
            id: btnStop
            text: "Stop"
            onClicked: myStopLight.state = "stop"//cách gán state TT
        }
        Button{
            id: btnGo
            text: "Go"
            onClicked: myStopLight.state = "go"
        }
        StopLight{
            id: myStopLight
            state: "stop"
        }
    }
}
