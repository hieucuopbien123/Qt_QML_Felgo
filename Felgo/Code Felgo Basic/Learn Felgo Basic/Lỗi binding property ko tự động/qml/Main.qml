import Felgo 3.0
import QtQuick 2.0

App {
    // You get free licenseKeys from https://felgo.com/licenseKey
    // With a licenseKey you can:
    //  * Publish your games & apps for the app stores
    //  * Remove the Felgo Splash Screen or set a custom one (available with the Pro Licenses)
    //  * Add plugins to monetize, analyze & improve your apps (available with the Pro Licenses)
    //licenseKey: "<generate one from https://felgo.com/licenseKey>"
    //Nếu cần thêm plugin có sẵn(Felgo cung rất nhiều) or Remove the Felgo Splash Screen,.. thì sẽ cần lisense key

    NavigationStack {//component của felgo=>quản lý các page trong memory, thêm bớt, hiển thị, xóa
        Page {//component của QML
            title: qsTr("Main Page ")

            Image {
                source: "../assets/felgo-logo.png"
                anchors.centerIn: parent
            }
            Text{
                property var test: model.checkTest()
                text: test ? qsTr("true") : qsTr("false")
            }
            Item {
                id: model
                property bool check: _.check
                anchors.centerIn: parent
                function checkTest(){
                    return _.check
                }

                GameButton {
                    text: "Click me!"
                    onClicked: {
                        if(_.check)
                            _.check = false
                        else
                            _.check = true
                        console.log(_.check + " " + model.check);
//                         _.checkChanged();
                    }
                }
                //Khi gán như trên thì model.check phụ thuộc vào _.check, khi _.check đổi thì model.check cx đổi nhưng
                //nếu 1 lúc nào đó ta chủ động gán model.check = false phát chẳng hạn thì nó lại k còn phụ thuộc vào
                //_.check nx=> tính chất binding ban đầu biến mất khi ta gán cho biến theo kiểu khác

                //Các property của 1 class chỉ truy cập được trong class đó, k dùng đc trong class cả con và cha, nếu
                //muốn dùng ở con và cha thì phải dùng id.

                //Với các thuộc tính của 1 class thì khi dùng bind property hầu hết nó đều thực hiện với signal slot tự
                //động. Các thuộc tính ta tạo ra bằng từ khóa property thì nó tự sinh ra 1 signal ngầm là
                //<tên class>.<tên property>Changed(paras); và slot ngầm là on<tên property>Changed: {}
                //Nhưng kp lúc nào các thuộc tính ta tạo ra với property đều tự động. VD đổi thuộc tính ở trong slot
                //xử lý 1 signal mà đổi thì nó sẽ k phát ra dẫn đến ta phải làm thủ công đổi nó bằng cách chủ động
                //phát signal thì mới đc. Điều này rất nguy hiểm vì đa phần các TH đều đổi, nếu 1 lúc nào nó k đổi thì
                //phải nghĩ đến cái lỗi này
                //Cái lỗi mất dậy này chỉ xuất hiện thỉnh thoảng khi ta thao tác với js thg là mảng kiểu thêm vào bỏ ra
                //thì bị chứ có lúc bị có lúc k bị. Nếu k bị mà ta lại gọi thì nó thực hiện vc bind 2 lần. Điều này làm
                //ta phải tự kiểm tra khi nào k đc mới tự phát
                Item {
                    id: _
                    property bool check: false
                    onCheckChanged: {
                        console.log("Check changed")
                    }
                }
            }
        }
    }
}
