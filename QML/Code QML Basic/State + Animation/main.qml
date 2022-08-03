import QtQuick 2.12
import QtQuick.Window 2.12

Window {
    width: 640
    height: 480
    visible: true
    title: qsTr("Hello World")
    id: root
    AnimationItem{}
    Rectangle {
        //đặc biệt là k đc dùng root mà phải dùng parent->các con của window k đc dùng id
        anchors.bottom: parent.bottom
        anchors.horizontalCenter: parent.horizontalCenter
        width: 100
        height: 300
        color: "black"
        state: "go"
        Rectangle {
            anchors.topMargin: 10
            anchors.top: parent.top
            width: 100
            height: 100
            radius: 90
            color: "gray"
            id: above
        }
        Rectangle {
            anchors.topMargin: 20
            anchors.top: above.bottom
            width: 100
            height: 100
            radius: 90
            color: "gray"
            id: below
        }
        states: [
            State {
                name: "go"
                PropertyChanges {
                    target: above
                    color: "darkred"
                }
                PropertyChanges {
                    target: below
                    color: "green"
                }
           },
           State {
               name: "stop"
               PropertyChanges {
                   target: above;
                   color: "red"
               }
               PropertyChanges {
                   target: below
                   color: "darkgreen"
                }
            }
        ]
        transitions: [
            Transition {
                from: "*"
                to: "*"
                PropertyAnimation {
                    target: above
                    property: "color"
                    duration: 500
                }
                PropertyAnimation {
                    target: below
                    property: "color"
                    duration: 500
                }
            }
        ]
        MouseArea{
            anchors.fill: parent//vì rectangle k có onClicked
            onClicked: {
                parent.state = (parent.state === "go") ? "stop" : "go"
            }
        }
    }
}
