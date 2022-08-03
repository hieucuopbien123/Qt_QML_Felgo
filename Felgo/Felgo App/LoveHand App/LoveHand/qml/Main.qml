import Felgo 3.0
import QtQuick 2.0

App {
    onInitTheme: {
        Theme.navigationBar.backgroundColor = "green"
        Theme.colors.textColor = "black"
      }
    //Theme thì hầu như felgo có tất cả theme về tất cả mọi thứ trong app-> có thể chỉnh sửa và lấy ra dùng tùy ý như này

    LoveHandMainItem{
        anchors.fill: parent
    }
}
