import QtQuick 2.15
import QtQuick.Window 2.15

Window {
    width: 640
    height: 480
    visible: true
    title: qsTr("Hello World")
    //Tương tự App của felgo, Window k hiển thị trong QML
    Item1Form {
        width: parent.width
        height: parent.height
    }
}
