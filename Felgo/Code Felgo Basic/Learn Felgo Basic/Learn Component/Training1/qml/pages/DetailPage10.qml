import QtQuick 2.15
import Felgo 3.0

FlickablePage {//có sẵn luôn
    id: page10
    AppTextField {
        id: field
        width: parent.width
        validator: RegExpValidator {
            regExp: /[0-9A-F]+/
        }
    }//regExp của JS y hệt
    Text {
        id: text
        anchors.top: field.bottom
        text: "Hello"
    }

    QtObject {
      id: internal
      objectName: "Hello"
      property string test: "string"
    }
    //QtObject là 1 component k hiển thị có mỗi object name=> có thể dùng nó để
    //lưu các thuộc tính nếu nhiều thuộc tính nhìn rôi

   // set contentHeight of flickable to allow scrolling
   flickable.contentHeight: column.height
   //cái Flickable trở thành 1 con của FlickablePage và truy cập với flickable,tương tự với scrollIndicator
   scrollIndicator.visible: true//mặc định cx là true=>thanh scroll ở đây xin hơn Flickable + scrollIndicator chay

   Column {
     id: column
     width: parent.width
     anchors.top: text.bottom
     //thay vì cứ anchor top với bottom, ta cho vào 1 column sẽ hay hơn

     Repeater {
       model: 10
       delegate: Rectangle {
         width: parent.width
         height: dp(50)
         AppText {
           anchors.centerIn: parent
           text: qsTr("Item") + " " + index
         }
       }
     }
   }
   AppActivityIndicator{
       anchors.centerIn: parent
       color: "red"
       animating: true
       animationDuration: 500//quay nhanh hơn
       icon: IconType.archive
       //mặc định là cái icon loading nhưng ta có thể tùy ý đổi
   }//khác cái baritem vì dùng chỗ nào cx đc
   //khi dùng centerIn cái page nhưng Page của ta cực dài nó sẽ fix ở giữa
   RoundedImage{
       width: dp(100)
       radius: width/2
       height: width
       source: "../../assets/felgo-logo.png"
       border.width: dp(2)
       border.color: "lightgrey"
   }
}
