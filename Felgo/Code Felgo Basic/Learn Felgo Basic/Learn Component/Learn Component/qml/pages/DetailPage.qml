import QtQuick 2.0
import Felgo 3.0

Page {
    useSafeArea: false
    title: "Page 0"
    ListPage{
        model: [
            {text: "Item 1", detailText: "Detail 1"},
            {text: "Item 2", detailText: "Detail 2"}
        ]
        delegate: /*SwipeOptionsContainer{
            id: container*/
            SimpleRow{
                id: row//thật ra trong 1 list như này SimpleRow nằm ở thành phần delegate của list
                //sẽ tự đc gán item: <model>.get(item) mà ta kp gán thủ công
            }
//            leftOption: SwipeButton{
//                text: "Option"
//                icon: IconType.gear
//                height: row.height//lấy kích thước row
//                onClicked: {
//                    row.item.text = "Option clicked"
//                    row.itemChanged()// phát signal ra thôi
//                    container.hideOptions()
//                }
//            }
//            rightOption: IconButton{//cho Component gì vào cx đc nhưng nhỏ thôi
//                selectedColor: "red"
//                icon: IconType.btc
//                height: row.height
//                onClicked: {
//                    container.hideOptions()
//                }//chú ý khi set right/leftOption thì phải set kích thước
//                //mặc định bth nó chỉ cho phép swipe 1 row của list mà thôi, swipe row khác thì row cũ sẽ tự đóng
//            }
//        }
    }

    AppButton{
        id: buttonTimer
        anchors.centerIn: parent
        text: enabled ? "Start job" : "Running..."
        enabled: true//lấy trạng thái running hay k
        fontBold: true
        fontCapitalization: Font.SmallCaps
        radius: dp(20)
        iconRight: IconType.bicycle
        iconLeft: IconType.youtubesquare
        icon: IconType.apple
        minimumWidth: 0
        minimumHeight: 0
        horizontalMargin: 0//chỉnh 1 phát cả 2 bên
        verticalPadding: 0
        leftItem: Rectangle{//dùng icon or custom 1 Component bất kỳ(nhỏ thôi)
            width: dp(15)
            height: width
            rotation: 45
            color: "green"
            opacity: Theme.isIos && buttonTimer.pressed ? 0.5 : 1//bởi vì iOS khi ấn nó vị mờ
        }

        onClicked: {
            enabled = false
            job.start()
        }
    }

    Timer{
        id: job
        interval: 2000
        repeat: false
        onTriggered: {
            console.log("Running");
            buttonTimer.enabled = true
            console.log(buttonTimer.enabled)
        }
    }
}
