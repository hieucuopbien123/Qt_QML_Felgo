import QtQuick 2.12
import QtQuick.Window 2.12
import QtQuick.Controls 2.0

Window {
    width: 500
    height: 500
    visible: true

    MouseArea{
        anchors.fill: parent
        onClicked: {
            recCenter.width = parent.width/4
            recCenter.height = parent.height/4
        }//trong sự kiện phải dùng dấu bằng
    }

    Slider{
        id: slider
        width: parent.width
        from: 0
        to: 360
        onValueChanged: {
            recCenter.rotation = slider.value
        }//k khai báo vị trí cho mặc định nó bắt đầu từ gốc 0,0
    }

    Rectangle{
        id: recCenter
        width: parent.width/2
        height: parent.height/2
        color: "green"
        anchors.centerIn: parent
        SmallGreenBox{
            id: recTopLeft
            anchors.right: recCenter.left
            anchors.bottom: recCenter.top
        }
        SmallGreenBox{
            id: recLeft
            anchors.right: recCenter.left
            anchors.verticalCenter: recCenter.verticalCenter//vị trí giữa của hình này nằm tại : vị trí giữa của recCenter
        }
        SmallGreenBox{
            id: recLeftBottom
            anchors.right: recCenter.left
            anchors.top: recCenter.bottom
        }
        SmallGreenBox{
            id: recTopCenter
            anchors.bottom: recCenter.top
            anchors.horizontalCenter: recCenter.horizontalCenter
        }
        SmallGreenBox{
            id: recTopRight
            anchors.left: recCenter.right
            anchors.bottom: recCenter.top
        }
        SmallGreenBox{
            id: recRight
            anchors.left: recCenter.right
            anchors.verticalCenter: recCenter.verticalCenter
        }
        SmallGreenBox{
            id: recBottomRight
            anchors.left: recCenter.right
            anchors.top: recCenter.bottom
        }
        SmallGreenBox{
            id: smallRecCenter
            anchors.centerIn: recCenter
        }
    }

    SmallGreenBox{
        id: recBottomCenter
        anchors.top: recCenter.bottom
        anchors.horizontalCenter: recCenter.horizontalCenter
        //horizontalCenter chú ý là căn giữa ngang đó
    }
}
//mối quan hệ: nếu dùng anchors nó chỉ cho ta set vị trí tương đối cố định với 1 cái gì đó->ví dụ xoay cái hình lớn,
//các hình nhỏ anchors vào các cạnh vẫn cố định, chỉ là 1 cách thay thế kiểu truyền số cố định cho dễ hơn.
//Tức là nếu dùng x, y cố định mà là child thì parent đổi nó vẫn đổi vì x,y là vị trí tương đối so với (0,0) of parent
//Nếu dùng child-parent thì các hình lớn đổi, các hình nhỏ cx đổi
