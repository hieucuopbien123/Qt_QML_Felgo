import QtQuick 2.12
import QtQuick.Window 2.12
import QtQuick.Controls 2.12

Window {
    width: 900
    height: 500
    visible: true
    title: qsTr("Canvas")
    id: window
    Row {
        spacing: 2
        id: row
        width: parent.width/2
        height: 100
        Button {
            text: "Save"
            anchors.right: parent.right
            anchors.rightMargin: 10
            //chú ý padding có ý nghĩa chỉnh content trong phạm vi của control chứ k thể làm rộng button ra đc
            //chỉnh width,height nó mới rộng ra. Ví dụ cho text dạt sang phải của button thì phải chỉnh padding
            width: contentItem.implicitWidth + leftPadding + rightPadding + 10
            height: contentItem.implicitHeight + topPadding + bottomPadding + 10
//            implicitWidth là chiều dài tự nhiên content bên trong
            onClicked: {
                testClass.testQMLClass(this.width);
            }
        }
        Button {
            text: "Clear"
            anchors.left: parent.right
            anchors.leftMargin: 10
            id: button
            width: contentItem.implicitWidth + leftPadding + rightPadding + 10
            height: contentItem.implicitHeight + topPadding + bottomPadding + 10
            onClicked: {
                canvas.reset()
            }
        }
    }
    //vị trí ta luôn cố gắng k set fix mà cái này luôn phụ thuộc vào cái khác chỉ cần anchors con theo cha là đã
    //đủ để set các vị trí tương đối và phụ thuộc hầu hết các vị trí luôn vì còn có anchors.margins mà
    Canvas {
        id: canvas
        width: parent.width
        height: parent.height - button.height
        anchors.topMargin: button.height//k đc có số liệu mà phải phụ thuộc
        //chú ý topMargin chỉ hoạt động khi có anchors.top r thì nó mới có cái mà theo chứ
        anchors.top: parent.top

        property int lastX: 0
        property int lastY: 0

        function reset(){
            var context = getContext("2d");
            context.reset();
            canvas.requestPaint();//hàm này là của canvas
        }
        onPaint: {
            var context = getContext("2d");
            context.lineWidth = 2
            context.strokeStyle = "green"
            context.beginPath();
            context.moveTo(lastX,lastY)
            lastX = area.mouseX
            lastY = area.mouseY
            context.lineTo(lastX,lastY)
            context.stroke();
            var lastPoint = Qt.point(lastX,lastY)
        }
        MouseArea {
            id: area
            anchors.fill: parent
            onPressed: {
                canvas.lastX = mouseX//mouseX mouseY là tự có trong mouseArea luôn lưu lại VT hiện tại trong mouseArea
                canvas.lastY = mouseY
            }
            onPositionChanged: {
                canvas.requestPaint();
            }
        }
    }
    //Chú ý row/col có height/width = 0 theo thứ tự đó, chứ kp theo các item bên trong nên chú ý anchors
    //Với id thì ta có thể truy cập vào các thông số của object vào mọi lúc, nhưng anchors thì kp mọi
    //lúc. anchors chỉ áp cho sibling, và con theo cha mà thôi, VD con của sibling thì k đc. Còn với id thì cái logic nó
    //phải đúng, ta hoàn toàn có thể set width của cha theo con, khi compile đến đó nó tìm trong các con nếu có con trùng
    //id đó thì compile con trc r quay lại gán thông số cho cha. Nhưng nếu ta cho width cha = width con xong bên trong
    //con lại gán width con = width cha thì hiển nhiên k chạy r

    //muốn cho canvas vừa vặn màn hình và dưới 2 cái button thì có thể bao row bằng 1 rectangle là đc vì row nó k dãn
    //cái width, xong cho rec theo width của button trong nó; cách 2 là dùng anchor bth với margin lấy dimension of button
}
