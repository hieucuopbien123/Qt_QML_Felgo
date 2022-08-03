import QtQuick 2.15
import QtQuick.Window 2.15
import QtQuick.Controls 2.1
import QtWebView 1.1
import "test.js" as Hello

Window {
    width: 640
    height: 480
    visible: true
    title: qsTr("Hello World")
    Rectangle{
        id: rec
        width: 100
        height: 100
        color: x == parent.width - width ? "red" : "green"
    }
    Button{
        id: save
        text: "Save"
        onClicked: {
            console.log('àdsdfsfds')
        }
    }
    MouseArea{
        anchors.fill: parent
        drag.target: rec
        drag.minimumX: 0
        drag.axis: Drag.XAxis
        drag.maximumX: parent.width - rec.width
        onClicked: {
            console.log(Hello.func())
        }
    }
    //Trap: Khi A đè lên B mà trigger sự kiện thì sẽ chỉ trigger của A. Ta tạo button xong MouseArea vô hình đè lên cả
    //màn hình thì ấn vào bất cứ chỗ nào cx trigger MouseArea vd ấn vào button chỉ trigger MouseArea, k trigger button
}
