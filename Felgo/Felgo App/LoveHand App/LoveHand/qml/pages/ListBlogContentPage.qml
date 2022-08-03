import QtQuick 2.0
import Felgo 3.0

ListPage {
    property var titleParam: "Mục yêu thích"
    property var modelParam: []
    property bool isFavourite: false
    title: titleParam
    emptyText.text: isFavourite ? "Không có bài viết yêu thích" : "Không có bài viết nào chủ đề này"

    model: JsonListModel{
        id: modelList
        source: isFavourite ? dataModel.favouriteList : modelParam
        //Lỗi: ta k dùng kiểu khi có favourite thì truyền favourite vào modelParam khác mà chơi kiểu biến bool
        //vì nếu làm như cách 1 sẽ lỗi rằng khi param cập nhập thì nó k load lại ngay
        //=>chú ý khi truyền vào 1 biến đối số 2 của hàm push của navigationStack thì biến đó sẽ k cập nhập ngay
        //Cụ thể là khi ta còn đang thao tác với biến con của page đó
        fields: ["title","content"]
    }
    Connections{
        target: dataModel
        onEditFinish:{
            if(isFavourite)
                modelList.remove(index)
        }
    }
    //chú ý các lỗi thg gặp nhất ở đây là lỗi cập nhập binding property.
    //Ở đây khi xóa favourite mặc dù nó chạy dataModel dữ liệu mới, modelList cx có dữ liệu mới nhưng nó k hiển thị
    //ra đúng ngay bởi vì ta phải chủ động thao tác move,remove,get,set,.. hết của các model nếu k nó sẽ dùng măc
    //dịnh là kiểm tra số phần tử r xóa từ cuối nếu phần tử ít hơn-> do đó ta phải chỉ đinh lại nó xóa đúng

    delegate: SimpleRow {
        detailText: item.title
        item: modelList.get(index)
        showDisclosure: true
        style: StyleSimpleRow{
            detailTextColor: "black"
            selectedTextColor: "green"
        }
        onSelected: {
            console.log(item.title)
            console.log(index)
            navigationStack.push(blogContentComponent,{titleParam: item.title, contentParam: item.content})
//            navigationStack.popAllExceptFirst()//đây là lệnh lùi lại cái page ở stack trước
            //có lúc nó kiểu bị như này k thể popAll and push đc mà phải như này-> có lẽ như này mới là chuẩn ấy
        }
    }
    Component{
        id: blogContentComponent
        BlogContentPage{ }
    }
}
