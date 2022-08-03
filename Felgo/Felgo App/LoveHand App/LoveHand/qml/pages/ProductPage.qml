import QtQuick 2.0
import Felgo 3.0

ListPage {
    useSafeArea: false
    title: "Sản phẩm"
    Component.onCompleted:{
        logic.queryProduct()
    }
    //onCompleted là signal chạy duy nhất 1 lần khi render đên nó lần đầu, về sau sẽ k chạy lại

    rightBarItem: ActivityIndicatorBarItem{
        visible: dataModel.loading
    }
    emptyText.text: "Hiện chưa có sản phẩm nào"

    model: JsonListModel {
        id: listModel
        source: dataModel.productList1
        fields: ["text","image"]
      }
    delegate: AppListItem{
        text: listModel.get(index).text
//        image: listModel.get(index).image
        image: Qt.resolveUrl("../../assets/felgo-logo.png")
        //có 2 loại url là url website và url file trong máy, 2 cái có scheme khác nhau
        //tùy loại property nếu cho phép url https mà ta chỉ có url file thì phải dùng Qt.resolveUrl ms đc
        //nó có vai trò resolve relative path url ở vị trí hiện tại
        imageSize: dp(height - contentPadding)
        onSelected: {
            navigationStack.push(productDetailComp, {model: listModel.get(index).model})
        }

        showDisclosure: true
    }
    Component{
        id: productDetailComp
        ProductDetailPage{}
    }

    //Nếu ta dùng kiểu thô sơ nhất là mảng TT thì chỉ cần khai báo SimpleRow là nó tự động có hết nhưng nếu
    //ta dùng thêm cái gì khác như JsonListModel thì phải gán item mới chạy đc.
    //Tuy nhiên SimpleRow bị hạn chế, nó k chỉnh được kích thước ảnh chẳng hạn thì AppListItem sẽ giải quyết tất cả
    //1 cách vô cùng đơn giản
}
