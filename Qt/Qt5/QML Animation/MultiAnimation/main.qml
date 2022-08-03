import QtQuick 2.12
import QtQuick.Window 2.12

Window {
    id: root
    width: 640
    height: 480
    visible: true
    title: qsTr("Hello World")
//animation như 1 lệnh chạy phát hết luôn, nếu ta k set loops cho nó thì sẽ hết, khi chạy phát nó xác định mọi thứ và chạy hàm
//do đó dù ta cho x chạy tới root.width nhưng khi resize window làm root.width đổi trong qtr di chuyển, nó vẫn lấy cái cũ
    Rectangle{
        id: box
        width: 50
        height: 50
        color: "green"
        opacity: 1
        /*NumberAnimation on x{
            to: root.width
            duration: 5000
        }
        NumberAnimation on y{
            to: root.height
            duration: 5000
        }*/
        SequentialAnimation{
            running: true

            NumberAnimation {
                target: box
                property: "x"
                duration: 5000
                to: root.width
                easing.amplitude: 0.3
                easing.period: 1.5
                easing.type: Easing.InOutBack
                //easing lo cách nó animation theo đồ thị, càng dốc càng nhanh, InOutBack là hiệu ứng đi quá r quay lại
                //quản lý với amplituded và period
            }
            NumberAnimation {
                target: box
                property: "y"
                duration: 5000
                to: root.height
            }
        }

        //dùng mặc định sẽ là ParallelAnimation
        RotationAnimation on rotation {
            from: 0
            to: 360
            duration: 1000
            loops: Animation.Infinite
        }
        ColorAnimation on color{
            from: "green"
            to: "red"
            duration: 3000
        }
    }

    NumberAnimation{
        id: opacity
        target: box
        running: true
        properties: "opacity"
        from: 1
        to: 0
        duration: 1000
        loops: Animation.Infinite
    }
//k cần lúc nào cx dùng phải on thuộc tính ở bên trong đối tượng, ta hoàn toàn có thể viết bên ngoài và điều khiển vc
//running là true hay false ở đây-> target và property là xong.
}
