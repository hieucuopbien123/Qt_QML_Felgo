import Felgo 3.0
import QtQuick 2.0

GameWindow {
    //cấu trúc game: GameWindow là component root của mọi game, mang kích thước vật lý của thiết bị. Tuy nhiên kích thước
    //của nó để fix là k tốt vì phải phụ thuộc vào thiết bị, khi đó ta dùng Scene trong GameWindow, khai báo cho nó là
    //kích thước nhỏ nhất của thiết bị. Khi đó GameWindow sẽ tự là kích thước màn hình thiết bị mặc kệ ta đã set fix cái
    //gì còn Scene sẽ scale lên fit với GameWindow(chỉ scale chứ k bị stretch)
    //Ví dụ ta set kích thước màn hình là 960x640(chú ý nó tự dùng màn hình landscape xoay ngang). Nếu ta gặp màn
    //hình 1000 x 700 thì to hơn bth thì màn hình game của ta vẫn sẽ là 960x640-> như thế là 0 tốt. Nếu ta dùng thêm Scene
    //thì nó sẽ khai báo kích thước màn hình nhỏ nhất của game-> nếu gặp thiết bị 1000x700-> GameWindow tự chuyển thành
    //kích thước màn hình hiện tại. Còn Scene sẽ scale theo màn hình của GameWindow hiện tại sao cho hiển thị full trên
    //màn hình(chỉ fit chứ k crop nên có thể thừa)
    //là scale kích thước của scene nên có height = 700, width tự theo với tỉ lệ của gamewindow
    //Tức là khi dùng Scene cho GameWindow có thể k set screenWidth/Height cho GameWindow cx đc, nó tự mang kích thước màn
    //hình vật lý bên ngoài
     id: gameWindow
     screenWidth: 960
     screenHeight: 480

    Rectangle {
        width: gameWindow.width
        height: gameWindow.height
        color: "black"
    }

    Scene {
        id: scene
        width: 480
        height: 320
        property int score: 0
//        rightclick thuộc tính->find để tìm các vị trí dùng nó trong dự án

        Rectangle {
            anchors.fill: scene.gameWindowAnchorItem
//         gameWindowAnchorItem là cái giúp anchors 1 item của scene với cái gamewindow chứa cái scene đó
//         làm như này thì dù cái rec này là 1 item trong scene nhưng nó lại full kín cái màn hình của ta như 1 cái
//         background. Các item khác vẫn chỉ hoạt động trong scene mà thôi. Cái này thường dùng trong các kiểu app màn
//         hình bé tí nhưng khi có màn hình to hơn sẽ k có vùng nào k hiện thị cả vì đã set kích thước background là full
//         màn hình r kể cả cái scene có bé tí đi chăng nx.
            color: "#324566"
        }
        Text {
            text: "Score: " + scene.score
            color: "white"
//            anchors.horizontalCenter: scene.horizontalCenter
//            anchors.top: scene.top
            anchors.horizontalCenter: scene.gameWindowAnchorItem.horizontalCenter
            anchors.top: scene.gameWindowAnchorItem.top
//            Tức là scene là cái màn hình game ta mong muốn, nhưng thực tế khi dùng vị trí ta lại muốn thao tác với
//            màn hình chuẩn của thiết bị vật lý thì phải dùng gameWindowAnchorItem
        }

        Column {
            anchors.centerIn: scene
            spacing: 10
            MyButton {
                labelText: "Add 1"
//                Với các component tự tạo ở file riêng có thể truyền như này r khai báo và dùng property ở trong file
                onClicked: {
//                scene.score++
                scene.increaseScore(1)
                }
            }
         MyButton {
           labelText: "Add 10"
           onClicked: {
             scene.increaseScore(10)
           }
         }
       }
       Image {
            id: image
            source: "../assets/felgo-logo.png"
            width: 100
            height: 100
            x: 0
            y: 0
       }
       SequentialAnimation {
            id: imageAnimation
            NumberAnimation {
                target: image
                property: "x"
                from: 0
                to: 15
                duration: 150
            }
            NumberAnimation {
               target: image
               property: "x"
               from: 15
               to: 0
               duration: 150
               //cái animation này sẽ k thực hiện tiếp nếu cái đợt animation lần trước
               //vẫn chưa thực hiện xong, nó sẽ bỏ qua cái animation mới cho đến khi thực hiện xong cái cũ
            }
       }
       Timer {
           //dùng trong scene hết mấy cái này vì đây là phạm vi game
            interval: 1000
            running: true
            repeat: true
            onTriggered: {
                scene.increaseScore(1)
            }
       }
       function increaseScore(amount) {
            scene.score += amount
            imageAnimation.start()
       }
  }
}
