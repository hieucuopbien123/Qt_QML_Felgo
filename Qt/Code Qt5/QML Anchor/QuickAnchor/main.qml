import QtQuick 2.15
import QtQuick.Window 2.15

Window {
    id: window
    width: 640
    height: 480
    visible: true
    Rectangle{
        id: root
        width: parent.width/2
        height: parent.height/2
        //khi width parent (ở đây là window) doi thi hcn nay cx doi, gán số sẽ gán fix
        color: "darkgreen"
        anchors.centerIn: parent
    }
    Rectangle{
        id: smallRec
        width: 50
        height: 50
        radius: width*0.5
        color: "red"
        anchors.top: root.top
        anchors.left: root.left
        //k cần là child vân nằm trong đc
        //nếu gán left của 1 hình trùng với top hình khác->sai vị trí sẽ về default (0,0)
    }
    //với các sibling, hình nào viết sau sẽ đè lên hình trc
    Rectangle{
        width: 100
        height:100
        color: "blue"
        anchors.top: smallRec.bottom
        anchors.left: smallRec.right
        anchors.margins: -10
        //k thể dùng left - 10 mà dùng margin vì mấy cái kia kp kiểu int mà là kiểu AnchorLine
        Rectangle{
            width: 50
            height: 50
            color: "yellow"
            anchors.margins: 10
            //margins ở đây k hđ, vì phải dùng kèm với căn lề ms đc
            anchors.top: parent.top
            //chú ý anchors chỉ dùng nối với item là parent or sibling(qua id),VD: dùng anchors.left:root.left ở đây là sai
            //dù parent có margin thì nó coi gốc của parent vẫn là (0,0), margin coi là chỉnh gốc 0,0
        }
    }
}
