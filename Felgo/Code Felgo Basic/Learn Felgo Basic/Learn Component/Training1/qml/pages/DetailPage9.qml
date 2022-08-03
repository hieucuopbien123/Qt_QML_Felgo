import QtQuick 2.0
import Felgo 3.0
import QtQuick.Layouts 1.11

Page {
    id: page9
    useSafeArea: true
    title: "Page 9"
    GridLayout{
        //gridlayout sẽ tự mở rộng theo các thành phần bên trong. Ta có thể gán width cho nó
        //r bên trong dùng fillWidth đc để cho cái textfield full màn hình còn lại, báo lỗi kệ nó
        columns: 12
        rows: 100
        rowSpacing: dp(2)
        columnSpacing: dp(2)
        Text { text: "Three"; font.bold: true; Layout.columnSpan: 3; Layout.alignment: Qt.AlignHCenter }
        Text { text: "words"; color: "red" }
        Text { text: "in"; font.underline: true; Layout.row: 2; Layout.column: 0 }
        Text { text: "a"; font.pixelSize: 20 }
        Text { text: "row"; font.strikeout: true; Layout.row: 3 }
        AppText{
            id: appText
            Layout.row: 4
            text: "Name: "
            Layout.columnSpan: 3
            Layout.topMargin: 10
        }
        AppTextField{
//            Layout.fillWidth: true//fill phần còn lại
            Layout.preferredWidth: 200
            //Các thứ như Text thì có thể mở rộng Column span đc nhưng các thứ như AppTextField thì phải chỉnh hẳn
            //kích thước của nó là preferredWidth
            //các item ở trong Layout chỉ đc muốn chỉnh kích thước thì phải dùng tiền tố Layout.
            onTextEdited: {//phát ra khi text được thay đổi bằng cách edit. VD ta bind property cho nó thì cx là thay
                //đổi nhưng kp do tự tay edit nên k phát ra, khác với onTextChanged phát hết
//                cache.setValue("Name","Hieu")
                console.log(cache.getValue("Name"))
                appText.text = cache.getValue("Name")
//                //Storage sẽ vẫn lưu dữ liệu đó làm cache mãi nên ta phải nhớ phải có hàm xóa khi cần nếu k
//                //tích lâu ngày ứng dụng sẽ rất lớn. Nó như setting v
//                cache.clearValue("Name")
//                cache.clearAll()
            }
        }
    }
    //=>có thể tạo user input form bằng Column Row bth or dùng grid đều đc
    Storage{
        id: cache
    }
}
