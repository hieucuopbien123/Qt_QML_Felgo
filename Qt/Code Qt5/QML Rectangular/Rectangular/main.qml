import QtQuick 2.12
import QtQuick.Window 2.12

Window {
    //k set, kich thước window sẽ mặc định khá nhỏ
    visible: true
    title: qsTr("Hello World")
    //qsTr cũng là tr trong qt hàm cần để dịch text
    color: "lightblue"
    MouseArea{
        anchors.fill:parent
        //ta đã biết khi k set width thì nó sẽ hoặc =0 hoặc mang giá trị là các thành phần bên trong như image/row nó tự
        //mở rộng khi set các tp bên trong. MouseArea cx v, mặc định là 0. Nhưng ta dùng anchors.fill sẽ fill kích thước
        //của nó ra khắp parent. Nếu dùng anchors.centerIn thì kích thước sẽ là 0,0 ở tâm trả có gì hết
        onClicked: {
            Qt.quit();
        }
        //kích hoạt sự kiện clicked; Qt là biến đang kích hoạt cái file qml này là QQmlApplicationEngine
        //và nó quit qml sẽ phát signal quit. Nó tự động connection QQmlApplicationEngine phát signal quit thì
        //QCoreApplication chạy slot quit Ct Qt C++ nên tự quit luôn, ta k phải tự tay làm
    }

    Text {
        id: name
        text: qsTr("He<i>llo</i> World")
        anchors.fill: parent
    }
    //anchors CB xác định vị trí->centerIn là vật nằm giữa vật gì; fill là vật bao phủ trong vật gì từ vị trí (0,0 trở đi)
    //do text bị giới hạn nên hiển nhiên k fill đc toàn bộ parent r nên cái này như cái left và top trùng parent thôi
    //anchors giúp ta set vị trí theo kiểu tương đối, k cần set x, y với số cụ thể
}
