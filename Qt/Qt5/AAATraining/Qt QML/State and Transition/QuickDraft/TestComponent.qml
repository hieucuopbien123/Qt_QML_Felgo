import QtQuick 2.12
import QtQuick.Controls 2.12

Slider{
    id: slider
    from: 0
    to: 100
    states: [//toàn quên ông state có s thôi => states
        State {
            name: "start"
            PropertyChanges {
                target: slider
                value: 0
            }
        },
        State {
            name: "end"
            PropertyChanges {
                target: slider
                value: 100
            }
        }
    ]
    transitions: [
        Transition {
            from: "*"
            to: "*"
            NumberAnimation{
                target: slider
                properties: "value,x"//vd nh thuộc tính thì dùng dấu phẩy ntn
                easing.type: Easing.InOutQuad
                duration: 1500
            }
        }
    ]
}
