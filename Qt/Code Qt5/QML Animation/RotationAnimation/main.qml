import QtQuick 2.12
import QtQuick.Window 2.12

Window {
    id: root
    width: 640
    height: 480
    visible: true
    title: qsTr("Hello World")

    property bool running: false

    Rectangle{
        id: body
        width: root.width
        height: root.height
        anchors.centerIn: root

        Image{
            id: background
            source: "qrc:/img/img/t2.jpg"
            anchors.centerIn: body
            fillMode: Image.PreserveAspectFit
            width: 1000
        //cái preserveAspectFit scale ảnh vào trong width height ta set k mất chi tiết k có gì đáng nói nhưng
        //cái centerIn cho body mà body đặt theo window khi ta resize sẽ thay đổi liên tục-> tâm bức ảnh luôn ở tâm window

            RotationAnimation on rotation{
                from: 90
                to: -360 - 90
                duration: 3000
                running: root.running
                //root.running la property cua root do ta set ben tren
                loops: Animation.Infinite
            }
        }
        Image{
            id: smallInside
            source: "qrc:/img/img/ballon.jpg"
            fillMode: Image.PreserveAspectFit
            width: 150
            opacity: 0.5
            anchors.centerIn: body
        }
//Vì nó tùy ý dùng id nên cái MouseArea nhét vào trong image hay ngoài như này đều chả sao nhưng ta nên sắp xếp dễ nhìn
        MouseArea{
            anchors.fill: background
            onClicked: root.running = root.running ? false : true
        }
    }
}
