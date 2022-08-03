import QtQuick 2.12
import QtQuick.Window 2.12

//Item là 1 qml type mà rất nhiều type khác kế thừa từ nó(cứ như là QObject trong qt c++ v).Item lại kế thừa QtObject
//kp tất cả các item đều dùng làm baseobject đc, ta buộc dùng window, nếu thay bằng rectangle chẳng hạn sẽ k chạy
//nếu muốn in hình phức tạp thì k nên vẽ mà nên render bức ảnh có sẵn ra
Window {
    width: 640
    height: 480
    visible: true
    title: qsTr("Hello World")

    Rectangle{
        height: 200
        width: 200
        color: "#ff0000"
        border.color: "#000000"
        border.width: 4
    }

    Rectangle{
        height: 200
        width: 200

        color: "green"
        border.color: "darkgreen"
        border.width: 4
        anchors.centerIn: parent
        Rectangle{
            height: parent.width/2
            width: parent.height/2
            radius: width*0.5
            x: 200
            y: 200
//1 object là con sẽ đè lên object parent. Vị trí tương đối x,y ta set là so với gốc của biến mẹ, kiểu trong biến mẹ
//nhưng nó có thể in ra ngoài phạm vi chỗ nào tùy ý ta chỉ cần màn hình đủ rộng để nhìn thấy
            color: "#ff0000"
            border.color: "#000000"
            border.width: 4
            anchors.left: parent.left//ưu tiên lấy theo anchors
            anchors.bottom: parent.bottom
        }
    }
}
