import QtQuick 2.12
import QtQuick.Window 2.12
import QtQuick.Controls 2.1

Window {
    width: 640
    height: 480
    visible: true
    Image {
        id: smile
        source: "https://i.pinimg.com/736x/5e/ef/2f/5eef2feed2770f1068e42f6a5ecc3538.jpg"
        //kèm chứng chỉ ssl vào phát là tải từ web tẹt bô ngay->k nên dùng ảnh trên mạng vì dễ lỗi
        onProgressChanged: {
            console.log("Progress: " + progress)
        }//progress chạy theo phần trăm từ 0->1
    }
    Image {
        id: ballon
        source: "qrc:/img/img/ballon.jpg"
        //trong qml k cần dấu : ở đầu mà dùng qrc: làm tiền tố or k dùng j
    }
    Slider{
        width: parent.width
        from: 0
        to: 360
        value: 0
        onValueChanged: {
            console.log(value)
            ballon.rotation = value
        }
    }
    AnimatedImage{
        id: banana
        source: "/img/img/banana.gif" //k có qrc: cx đc
        x: 25
        y: 25
        opacity: 0.5
    }

}
