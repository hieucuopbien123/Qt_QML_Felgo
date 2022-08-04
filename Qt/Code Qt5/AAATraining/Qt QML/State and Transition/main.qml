import QtQuick 2.15
import QtQuick.Controls 2.0

Window {
    width: 640
    height: 480
    visible: true
    title: qsTr("Hello World")
    Rectangle{
        width: parent.width
        height: parent.height
        anchors.centerIn: parent
        gradient: Gradient{
            orientation: Gradient.Horizontal
            GradientStop { position: 0.0; color: "green"}
            GradientStop { position: 1.0; color: "yellow"}
        }
        TestComponent{
            id: slider
            state: "start"
            width: parent.width
        }
        Button{
            anchors.centerIn: parent
            text: "Change state"
            onClicked: (slider.state === "start") ? (slider.state = "end") : (slider.state = "start")
        }
    }
}
