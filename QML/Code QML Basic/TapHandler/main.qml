import QtQuick 2.15
import QtQuick.Window 2.15

Window {
    width: 640
    height: 480
    visible: true
    title: qsTr("Hello World")
    Rectangle{
        color: "red"
        width: 100
        height: 100
        z: 1
        border.color: "black"
        border.width: 2
        gradient: Gradient{
            GradientStop{ position: 0.0; color: "green" }
            GradientStop{ position: 1.0; color: "yellow" }
        }

        Rectangle{
            width: 50
            height: 50
            color: tap.pressed ? "green" : "yellow"
            z: 0//z của con k thể nào nằm dưới cha đc nên ở đây vô hiệu dù z đc gán
            TapHandler{
                id: tap //tap handler thg dùng cho tay tap vào nhưng trên window là chuột.VD: onLongPressed
                onPressedChanged: {
                    console.log(parent.z)
                }
            }
        }
    }
}
