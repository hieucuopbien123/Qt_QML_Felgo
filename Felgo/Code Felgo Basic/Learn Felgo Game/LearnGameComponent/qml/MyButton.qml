import QtQuick 2.0
//custom 1 button từ đầu luôn

Rectangle {
    id: myButton
    width: label.width > 100 ? label.width : 100
    height: 50
    color: mouseArea.pressed ? "#546632" : "#32665a"

    property alias labelText: label.text
    signal clicked

    Text {
        id: label
        text: "DefaultText"
        color: "white"
        anchors.centerIn: parent
    }

    MouseArea {
        id: mouseArea
        anchors.fill: parent
        onClicked: {
            myButton.clicked()
//            scene.score++
//            chú ý truy cập vào property tự tạo phải thông qua id của component
        }
    }
}
//Do thuộc tính score là điểm số có thể tăng lên vì rất nhiều lý do, nên ta k nên dùng bind property kiểu này ở trong
//1 component trong file vì button là thứ có thể tái sử dụng ở nhiều nơi nên ta nên cho nó click là phát signal để dùng
//ở chỗ khác bằng cách bắt signal đó còn bind property sẽ dùng ở ngoài, nơi mà k ảnh hưởng đến vc tái sử dụng
