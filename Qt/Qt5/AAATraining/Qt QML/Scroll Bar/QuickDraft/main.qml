import QtQuick 2.15
import QtQuick.Window 2.15
import QtQuick.Controls 2.12

Window {
    width: 640
    height: 480
    visible: true
    title: qsTr("Hello World")
    Row{
        id: row
        width: parent.width
        height: parent.height/2//k set width, height thì coi row bẹp dí 1 hàng bên trên khi anchors
        ScrollView{
            width: parent.width/2
            height: parent.height
            TextArea{
                text: "Hello"
                selectByMouse: true
                font.pointSize: 20
            }
        }
        Flickable{
            width: parent.width/2
            height: parent.height
            contentHeight: contentItem.childrenRect.height
            contentWidth: contentItem.childrenRect.width
            clip: true
            TextArea.flickable: TextArea{
                text: "Hello"
                selectByMouse: true//set cái này flick sẽ mất bởi chuột nhưng vẫn còn hiệu ứng boundBeHaviours khá đẹp
            }
            ScrollBar.vertical: ScrollBar{}
        }
    }
    //ScrollBar ở trong component nào với đk component đó là các kiểu chứa như Flickable or ScrollView thì khi content
    //bị quá kích thước nó sẽ xuất hiện để hiển thị hết. Rectangle cũng tính
    Rectangle {
        id: frame
        clip: true
        width: parent.width
        height: parent.height/2
        anchors.top: row.bottom

        TextArea {
            id: content
            text: "Hello"
            font.pixelSize: 20
            x: -hbar.position * width
            y: -vbar.position * height
            //bản chất của việc di thanh scroll thì nhìn thấy phần chữ tiếp theo chính là move vị trí của chữ đi như này
            //position là chỉ vị trí thanh scroll trong khoảng nó có thể move từ 0 đến 1

            //thử đoán xem nếu set width:parent.width cho textarea chuyện gì xảy ra? thành hbar sẽ vô dụng vì width của
            //TextArea kbh vượt quá parent(kể cả chữ vượt ra ngoài) nên thanh hbar kbh xuât hiện nx
            //Chính vì kích thước của TextArea ở đây nó tự mở rộng theo text bên trong nên nếu gõ k hết 1 dòng thì nó chỉ
            //là 1 hình chữ nhật nhỏ phía bên trái. Ta ấn focus vào 1 dòng click chuột ở xa bên phải sẽ k focus đc. Nếu dùng
            //scrollView như trên thì focus ez. Ta có thể làm kiểu click vào rectangle thì textArea focus với signal slot
            //cx ok cho giống scrollview
        }

        ScrollBar {
            id: vbar
            hoverEnabled: true
            active: hovered || pressed
            orientation: Qt.Vertical
            //size ở đây vbar là kích thước của nó đúng bằng frame.height / content.height. Khi content.height tăng thì
            //kích thước sẽ co dần lại chứng mình có thể scroll nhiều hơn khi content rộng ra
            size: frame.height / content.height
            anchors.top: parent.top
            anchors.right: parent.right
            anchors.bottom: parent.bottom
            //phải set vị trí cho nó
        }

        ScrollBar {
            id: hbar
            hoverEnabled: true
            active: hovered || pressed
            orientation: Qt.Horizontal
            size: frame.width / content.width
            anchors.left: parent.left
            anchors.right: parent.right
            anchors.bottom: parent.bottom
        }
    }

}
