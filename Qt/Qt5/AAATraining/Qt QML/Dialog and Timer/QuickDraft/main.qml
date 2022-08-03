import QtQuick 2.15
import QtQuick.Window 2.15
import QtQuick.Controls 2.12
import Qt.labs.platform 1.0

Window {
    width: 640
    height: 480
    visible: true
    title: qsTr("Hello World")
    id: root
    ColorDialog{
        id: useColor
        modality: Qt.WindowModal
        title: "Choose Color"
        onAccepted: { console.log(`Accepted` + color) }
        onRejected: { console.log(`Rejected`) }
        options: ColorDialog.ShowAlphaChannel
    }
    FontDialog{
        id: useFont
        modality: Qt.WindowModal
        title: "Choose Font"
        onAccepted: { console.log(`Accepted` + font) }
        onRejected: { console.log(`Rejected`) }
    }

    Column {
        width: parent.width
        spacing: 2
        Row{
            Button{
                text: "Color"
                onClicked: {
                    useColor.open()
                }
            }
            Button{
                text: "Font"
                onClicked: {
                    useFont.open()
                }
            }
        }

        TextField{
            id: textField
            width: parent.width - 2*anchors.leftMargin
            leftPadding: 10
            topPadding: 10
            rightPadding: 10
            bottomPadding: 10
            //k có padding: 10 đâu mà phải xét từng cái
            height: 40
            anchors.left: parent.left
            anchors.leftMargin: 10//dùng anchors margin phải anchors nó trước
            onTextChanged: {
                textArea.text = Qt.btoa(text)
            }
            echoMode: TextInput.Password
            selectByMouse: true
            placeholderText: "Hello world!"
            placeholderTextColor: "green"
        }
        //Date nó thành 1 kiểu biến như trong js
        Text{
            property var date: new Date()
            property var locale: Qt.locale()
            text: date.toLocaleDateString(locale,Locale.LongFormat) + " " + locale.name
        }
        Text{
            //chú ý là trong qml k có time, nhưng Date của JS lưu cả time, ta có thể dùng time or datetime với
            //Qt.formatTime và Qt.formatDateTime
            property var date: new Date()
            text: Qt.formatTime(new Date(),"hh:mm:ss")
        }
        Text{
            property var date: new Date()
            text: Qt.formatDateTime(new Date(),"dd.MM.yyyy hh:mm:ss")//chú ý viết hoa viết thg
        }
        Text {
            id: time
        }
        Timer {//cái này dùng chỗ khác chứ dùng ở đây nó chèn vào 1 khoảng trống
            property int count: 1
            interval: 500
            running: count < 5 ? true : false
            repeat: true
            onTriggered: {
                count++
                time.text = Date().toString()
            }
            //giả sử muốn đăt điều kiện sau vài s thì dừng=> trong qml k viết đk bên ngoài đc mà phải như này, dùng ?:
        }
        Flickable{
            width: parent.width
            height: root.height - textField.height
            TextArea.flickable: TextArea{
                text: "Hello\nWorld!"
                leftPadding: 10
                topPadding: 10
                rightPadding: 10
                bottomPadding: 10
                id: textArea
                font: useFont.font
                color: useColor.color
                placeholderText: "Hello world!"
                placeholderTextColor: "green"
            }
            ScrollBar.vertical: ScrollBar{}
        }
    }
}
