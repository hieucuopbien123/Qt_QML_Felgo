import QtQuick 2.0
import Felgo 3.0

//dùng Connections với listPage bị lỗi nhưng các thứ khác thì vẫn ôn

ListPage {
    title: "Tiêu đề"
//    model: [{ type: "Fruits", text: "Banana"},
//        { type: "Fruits", text: "Apple" },
//        { type: "Vegetables", text: "Potato" }]//dùng TT
    model: JsonListModel{
        id: jsonModel
        source: [{ type: "Fruits", text: "Banana" },
                 { type: "Fruits", text: "Apple" },
                 { type: "Vegetables", text: "Potato" }]
        fields: ["type","text"]
    }
    delegate: SimpleRow{
        text: item.text//đè lên item, mặc định là item.text
        item: jsonModel.get(index)
//        imageSource: "https://www.imgacademy.com/themes/custom/imgacademy/images/helpbox-contact.jpg"
//        imageSource: "file:///C:/Users/Admin/AppData/Roaming/Felgo Live Client/untitled/assets/felgo-logo.png"
        imageSource: "file:///B:/Qt/FelgoNew/Training1/Training1/assets/felgo-logo.png"
        //imageSource nhận url khác với AppImage source bth nó nhận link thư mục. Khi nhận url thì buộc có scheme
        //file:///<link tuyệt đối> khi dùng thư mục trong may
        imageMaxSize: dp(80)
        autoSizeImage: true
        image.fillMode: Image.PreserveAspectFit
        //item phải gán cho nó 1 object có các trường là các attribute của SimpleRow, cơ bản nhất là có text,
        //image, detailText. Nếu như tên trường bị khác thì ta có thể gán thủ công như bên trên với text
        onSelected: {
            var pos = listView.getScrollPosition()
            console.log(index)
            listView.restoreScrollPosition(pos)
            //có thể lưu vị trí lại r khi nào cần thì cho quay lại
        }
    }

    //cơ bản nhất là model là 1 array các object
//    emptyText.text: "No Data To Display"
    emptyText{
        text: "No data To Display"
    }

    section.property: "type"//thuộc tính nào sẽ chia ra(thuộc tính có tác dụng chia như kiểu title sẽ k
    //thể chọn đc)
    listView.footer: VisibilityRefreshHandler{
        visible: true
        onRefresh: {
            console.log("Helloo")
        }//signal fresh chỉ đc phát ra khi cái biểu tượng quay quay xuất hiện do kéo xuống dưới cùng
        //nếu biểu tượng xuất hiện nhưng kp do kéo xuống dưới cùng thì k phát signal này. Do đó ta cần phải
        //set cái visible cho chuẩn là khi nào còn dữ liệu mới lấy tiếp
    }
    //trong ListPage nó dùng 1 cái AppListView và listView giúp ta truy cập vào nó
    //thuộc tính footer sẽ xác định component gì dùng ở footer
}
