import QtQuick 2.12
import QtQuick.Window 2.12
import QtQuick.Controls 2.12
import Qt.labs.platform 1.0
//import Qt.labs.platform 1.0 dùng dự phòng cho native dialog khi Qt 6 k còn hỗ trợ QtQuick.Dialogs nx
//nhưng phải dùng QApplication và QT+=widgets ms đc

Window {
    width: 640
    height: 480
    visible: true
    title: qsTr("Hello World")
    ColorDialog{
        id: colorDialog
        modality: Qt.WindowModal
        title: "Choose a color"
        color: "green"
        onAccepted: { console.log("Accepted: " + color) }
        onRejected: { console.log("Rejected") }
    }//chưa xử lý các thao tác sâu hơn trong dialog vội
    FontDialog{
        id: fontDialog
        modality: Qt.WindowModal
        title: "Choose a color"
        onAccepted: { console.log("Accepted: " + font) }
        onRejected: { console.log("Rejected") }
    }
    Row{
        Button{
            id: buttonColor
            text: "Color"
            onClicked: {
                colorDialog.open()
            }//k cần signal color change làm gì, gán TT cx tự connect signal slot
        }
        Button{
            id: buttonFont
            text: "Font"
            onClicked: {
                fontDialog.open()
            }
        }
        TextField{
            id: textField
            text: "<b>Enter</b> some text"
            placeholderText: "Example"
            width: 400
            selectByMouse: true
        }//tự có khung
    }
    Text {
        id: preview
        anchors.centerIn: parent
        font: fontDialog.font
        color: colorDialog.color
        text: textField.text
    }//Ta gán cho text của cái này là text của cái kia luôn vì nó cùng thuộc tính kiểu là text
    //Do đó k cần onTextChanged xong đổi thì gán mất tg, dùng luôn như này, tương tự font,color. Tự có signal slot ngầm
}
