import QtQuick 2.0

Rectangle{
    id: singage
    width: 100
    height: 250
    color: "yellow"
    border.color: "black"
    border.width: 1

    gradient: Gradient{
        GradientStop { position: 0.0; color: "yellow"}
        GradientStop { position: 1.0; color: "#B8B812"}
    }
    //gán gradient cho 1 biến gradient->k thể tạo nó là con được mà cx chả cần tạo 1 file riêng, dùng luôn như này

    Column{
        spacing: 50
        anchors.centerIn: parent
        Light{
            id: redLight
        }
        Light{
            id: greenLight
        }
    }

    states: [
        State {
            name: "stop"
            PropertyChanges { target: redLight; color: "red" }
            PropertyChanges { target: greenLight; color: "darkgreen"}
        },//nó là 1 mảng nên phải có comma
        State {
            name: "go"
            PropertyChanges { target: redLight; color: "darkred" }
            PropertyChanges { target: greenLight; color: "lime"}
        }//trong state dùng changes, trong transition dùng animation
    ]

    //transition cx la array
    transitions: [
        Transition{
            from: "*"
            to: "*"
            PropertyAnimation{ target: redLight; properties: "color"; duration: 500 }//tổng quát
            PropertyAnimation{ target: greenLight; properties: "color"; duration: 500; easing.type: Easing.InOutQuad }
        }//xác định transition tác động vào state vào của property nào của đối tượng nào
    ]
    //animation tự thực hiện như 1 lệnh từ đầu tới cuối, còn transition là sự chuyển cảnh từ trạng thái này sang TT khác
    //2 cái khá giống nhau ví dụ ở trên ta dùng animation bth cx đc
    //dùng animation trong transition để xác định transition như thế nào vì 2 cái giống nhau
}
