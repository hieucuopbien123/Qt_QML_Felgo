import Felgo 3.0
import QtQuick 2.0
import QtQuick.Controls 1.4
import QtMultimedia 5.9

App {

    function test(){
        HttpRequest.get("https://www.vietinbank.vn/")
        .then(function(res){
            console.log(res)
            var content = res.text
            console.log(content)
            try{
                var obj = JSON.parse(content);
                console.log(obj)
            }
            catch(ex){
                console.error("Could not parse JSON: " + ex);
            }
        })
        .catch(function(err){
            console.debug("Fatal error in URL GET");
        })
    }
    Component.onCompleted: {
        test()
    }

//    NavigationStack {

//        FlickablePage{
//            title: qsTr("Main Page")
//            flickable.contentHeight: name.height
//            scrollIndicator.visible: true
//            AppText {
//                id: name
//                text: "<strong>strong text</strong>"
//                wrapMode: Text.WrapAtWordBoundaryOrAnywhere
//                width: parent.width
//            }
//            AppButton{
//                anchors.centerIn: parent
//                text: "Fetch"
//                onClicked: test()
//            }
//        }
//    }

//    Rectangle {
//        width: 320
//        height: 200

//        AppPaper {
//            anchors.centerIn: parent
//            width: childrenRect.width + 50
//            height: childrenRect.height + 50

//            Text {

//                id: hello
//                x: 10
//                y: 10
//                text: "Hello"
//            }

//            Text {
//                anchors.left: hello.right
//                anchors.leftMargin: 10
//                anchors.top: hello.top
//                text: "World"
//            }
//        }
//    }
//lỗi bind loop: khi cha bind con, con bind cha; khi cha dùng childrenRect, còn lại centerIn; khi cha là AppPaper mà
    //lại dùng childrenRect=> tránh lỗi tốt nhất là dùng thủ công, chỉ dùng childrenRect vói các cái cơ bản

//    SwipeView {
//        id: view

//        currentIndex: 1
//        anchors.fill: parent

//        Item {
//            id: firstPage
//            AppText{
//                text: "Hello"
//            }
//        }
//        Item {
//            id: secondPage
//            AppText{
//                text: "World"
//            }
//        }
//    }

//    PageIndicator {
//        id: indicator

//        count: view.count
//        currentIndex: view.currentIndex

//        anchors.bottom: view.bottom
//        anchors.horizontalCenter: view.horizontalCenter
//    }

//    Column{
//        id: col
//        spacing: 2
//        Rectangle{
//            width: 100
//            height: 100
//            color: "red"
//        }
//        Rectangle{
//            color: "green"
//            AppButton{
//                text: "Click me"
//                onClicked: console.log(col.height)
//            }
//        }
//    }

//    ItemTest{}

//    Page{
//        width: 300
//        height: 500
//        Rectangle{
//            id: rec
//            width: parent.width
//            anchors.left: parent.left
//            anchors.right: parent.right
//            anchors.top: parent.top
//            anchors.margins: 20
//        }
//        AppButton{
//            anchors.centerIn: parent
//            text: "Show"
//            onClicked: {
//                console.log(rec.width)
//            }
//        }
//    }
    //chú ý width nó k tính margin. Nếu setWidth là parent lớn xong lại set margin thì giá trị width về sau phải
    //trừ đi margin

//    Rectangle {
//        id: rectangle
//        width: 567
//        height: 448
//        color: "green"
//        SwipeView{
//            id: swipe
//            width: 1000
//            height: 400
//            currentIndex: 1
//            Item {
//                id: appText
//                AppText {
//                    text: qsTr("Helo wordl")
//                }
//            }

//            Item {
//                id: appText1
//                AppText {
//                    text: qsTr("Hieu Nguyen")
//                }
//            }
//        }
//    }

//    Rectangle {
//        width: 500; height: 500

//        Component {
//            id: delegate
//            Column {
//                id: wrapper
//                Image {
//                    anchors.horizontalCenter: nameText.horizontalCenter
//                    width: 64; height: 64
//                    source: "../assets/felgo-logo.png"
//                }
//                Text {
//                    id: nameText
//                    text: name
//                    font.pointSize: 16
//                    color: wrapper.PathView.isCurrentItem ? "red" : "black"
//                }
//            }
//        }

//        ListModel {
//            id:listModel
//            ListElement {
//                  name: "Apple"
//                  cost: 2.45
//              }
//              ListElement {
//                  name: "Orange"
//                  cost: 3.25
//              }
//              ListElement {
//                  name: "Banana"
//                  cost: 1.95
//              }
//              ListElement {
//                  name: "Banana"
//                  cost: 1.95
//              }
//              ListElement {
//                  name: "Banana"
//                  cost: 1.95
//              }
//        }

//        PathView {
////            anchors.fill: parent
//            width: 500
//            height: 500
//            model: listModel
//            delegate: delegate
//            path: Path {
//                startX: 120; startY: 100
//                PathQuad { x: 120; y: 25; controlX: 260; controlY: 75 }
//                PathQuad { x: 120; y: 100; controlX: -20; controlY: 75 }
//            }
//        }
//    }


       // Displays a title bar and is used for navigation between pages
//       NavigationStack {

//         Page {
//           title: "Video" // Is displayed in the title bar

//           MediaPlayer {
//             id: mediaplayer
//             autoPlay: true
//             loops: MediaPlayer.Infinite
//             source: "https://felgo.com/web-assets/video.mp4"
//           }

//           VideoOutput {
//             anchors.fill: parent
//             source: mediaplayer
//           }
//         }
//       }

//    ListModel{
//        id: modelList
//        ListElement{
//            text: "1. Thiền"
//            detailText: "Thiền là một cách tắt những chương trình chạy ngầm để cơ thể và tâm hồn nghỉ\
//dưỡng đấy những bạn ạ."
//        }
//        ListElement{
//            text: "2. Làm đẹp"
//            detailText: "Đẹp giúp chúng ta tự tin hơn trong cuộc sống. Có câu “Không có người phụ nữ\
//xấu, chỉ có người phụ nữ không biết làm đẹp mình”."
//        }
//        ListElement{
//            text: "3. Làm giàu"
//            detailText: "Làm giàu là điều mà chúng ta luôn thực hiện trong cuộc đời mình. Thời trẻ\
//làm giàu về vật chất, về già lại muốn làm giàu về sức khỏe."
//        }
//        ListElement{
//            text: "4. Ẩm thực"
//            detailText: "Mọi thứ chúng ta ăn vào đều chuyển hóa thành năng lượng nuôi dưỡng cơ thể.\
//Năng lượng đó là tích cực hay tiêu cực phụ thuộc vào món ăn và thức uống mà chúng ta sử dụng."
//        }
//        ListElement{
//            text: "5. Giải trí"
//            detailText: "Giải trí đúng cách sẽ giúp bạn có được tinh thần tốt, một tâm thế tốt để\
//giải quyết công việc hàng ngày."
//        }
//        ListElement{
//            text: "6. Học"
//            detailText: "Bạn có thể học từ người thầy của mình, hoặc từ một người thành đạt, bạn\
//cũng có thể học từ bạn bè, từ đồng nghiệp và thậm chí từ những người lao công hay chú bảo vệ."
//        }
//        ListElement{
//            text: "7. Tâm linh"
//            detailText: "Có nhiều góc nhìn về tâm linh khác nhau, mỗi góc nhìn sẽ cho bạn một khái\
//nhiệm riêng biệt."
//        }
//        ListElement{
//            text: "8. Bệnh người già"
//            detailText: "Có nhiều góc nhìn về tâm linh khác nhau, mỗi góc nhìn sẽ cho bạn một khái\
//nhiệm riêng biệt."
//        }
//        ListElement{
//            text: "9. Bệnh trẻ em"
//            detailText: "Có nhiều góc nhìn về tâm linh khác nhau, mỗi góc nhìn sẽ cho bạn một khái\
//nhiệm riêng biệt."
//        }
//        ListElement{
//            text: "10. Bệnh thường gặp"
//            detailText: "Có nhiều góc nhìn về tâm linh khác nhau, mỗi góc nhìn sẽ cho bạn một khái\
//nhiệm riêng biệt."
//        }
//    }

// AppListView{
//     width: parent.width - contentPadding*2
//     model: modelList
//     delegate: SimpleRow{
//          item: modelList.get(index)
//     }
// }
    AppTextField{
        showClearButton: true
        width: parent.width
    }
}

//import Felgo 3.0
//import QtQuick 2.5
//import QtGraphicalEffects 1.0

//App {
//  NavigationStack {

//    ListPage {
//      id: page
//      title: "Blur Effect"

//      // get the total height of status bar and navigation bar
//      readonly property real barHeight: dp(Theme.navigationBar.height) + Theme.statusBarHeight

//      // navigation bar is 100 percent translucent, the page then also fills the whole screen
//      // this allows us to display a custom navigation bar background for this page
//      navigationBarTranslucency: 1.0

//      // list view only fills page area below navigation bar
//      listView.anchors.topMargin: barHeight

//      // add twenty dummy items to the list
//      model: 20
//      delegate: SimpleRow { text: "Item #"+index }

//      // custom navigation bar background that shows an image
//      Rectangle {
//        id: background
//        width: parent.width
//        height: page.barHeight
//        color: Theme.navigationBar.backgroundColor

//        // add the image
//        Image {
//          id: bgImage
//          source: "https://felgo.com/web-assets/felgo-logo.png"
//          anchors.fill: parent
//          fillMode: Image.PreserveAspectCrop

//          // the blur effect displays the image, we set the source image invisible
//          visible: false
//        }

//        // apply blur effect
//        FastBlur {
//          id: blur
//          source: bgImage
//          anchors.fill: bgImage

//          // the strength of the blur is based on the list view scroll position
//          radius: Math.max(0, Math.min(64, page.listView.contentY/3))
//        }
//      } // Rectangle
//    }// ListPage

//  }
//}
