import QtQuick 2.0
import Felgo 3.0

Page {
    property int number: 0
    useSafeArea: true
    title: "Page 6"
    AppTextField{
        width: parent.width
        showClearButton: true
        placeholderText: number
        inputMethodHints: Qt.ImhNoPredictiveText//loại keyboard gì hiện ra chứ ng dùng nhập
        //cái khác thoải mái
        onEditingFinished: {
            console.log(placeholderText)
        }
        backgroundColor: "black"
        borderColor: "blue"
        borderWidth: Theme.isAndroid ? (2) : 0
        textColor: "white"
        placeholderTextColor: Theme.dividerColor//or dùng placeholderColor
        //dividerColor là cái màu của cái divider giữa các row đó, override để đổi các thuộc
        //tính mặc định này đc
        echoMode: TextInput.PasswordEchoOnEdit//lúc edit lần đầu thì hiện chữ
    }
    Flickable{
      anchors.centerIn: parent
      Text{
          text: "Hello"
      }
      ScrollIndicator {
        flickable: scroll
      }
    }
    BackgroundImage{
        source: "https://www.imgacademy.com/themes/custom/imgacademy/images/helpbox-contact.jpg"
        fillMode: Image.PreserveAspectCrop
        clip: true
        opacity: 0.7
        z: -1
    }
    //BackgroundImage cx chỉ là AppImage bình thường nhưng nó kiểu hỗ trợ multi resolution. Ta chưa quan
    //tâm mà chỉ cần biết set opacity và trục z: -1 để đưa nó về sau các component khác mà thôi
}
