import QtQuick 2.12
import QtQuick.Window 2.12
import QtQuick.Controls 2.12

Window {
    width: 640
    height: 480
    visible: true
    title: qsTr("Hello World")
    Rectangle{
        width: height*2//Js in binding
        height: getHeight()//js in function
        color: x > 300 ? "red" : "limegreen"//js binding
        function getHeight(){
            return 100;
        }

        id: rec
    }
    MouseArea{
        anchors.fill: parent
        drag.target: rec
        drag.axis: Drag.XAxis
        drag.minimumX: 0
        drag.maximumX: parent.width - rec.width
    }
}
