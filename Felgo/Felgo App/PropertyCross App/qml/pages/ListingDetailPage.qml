import QtQuick 2.0
import Felgo 3.0

Page {
    property var model: ({})//ban đầu k có gì, phải dùng ({}) để khai báo empty obj literal
    //kể cả ta truyền vào nhưng nó k tự có, ta phải định nghĩa 1 cái tên trùng ở đây thì mới dùng bên trong
    title: qsTr("Property details")
    readonly property bool isFavourite: dataModel.isFavourite(model)
    //Page này nhận model và hiển thị thôi. Ta phải kiểm tra xem nó có phải là favourite hay k.
    //Từ cái model nhận đc mà ta kiểm tra xem có phải favourite hay k, ta sẽ kiểm tra trong dataModel sau vì nó sẽ xử lý
    //favourite về sau
    rightBarItem: IconButtonBarItem{
        icon: isFavourite ? IconType.heart : IconType.hearto//hearto là empty heart=> lo vc hiển thị thôi
        //gán như này icon sẽ thay đổi bất cứ lúc nào isFavourite đổi
        onClicked: {
            console.log(model)
            logic.toggleFavourite(model)
            //ấn thích thì sẽ phát signal lưu cái model này lại vào mục favourite, tức phát ra cái model này để nó lưu
            //data model sẽ bắt và xử lý signal này phát ra từ logic(dataModel sẽ xử lý favourite)
        }
    }
    clip: true//thuộc tính clip của page cho rằng item sẽ clip content của nó và cả children của nó theo cái khung chữ
    //nhật bên ngoài
    Flickable {
        id: scroll
        anchors.fill: parent
        contentWidth: parent.width
        contentHeight: contentCol.height + contentPadding
        bottomMargin: contentPadding
        Column {
            id: contentCol
            y: contentPadding
            anchors.left: parent.left
            anchors.right: parent.right
            anchors.margins: contentPadding
            spacing: contentPadding
            AppText {
                text: model.price_formatted
                width: parent.width
                wrapMode: Text.WrapAtWordBoundaryOrAnywhere
                font.pixelSize: sp(24)
            }
            AppText{
                text: model.title
                width: parent.width
                wrapMode: Text.WrapAtWordBoundaryOrAnywhere
                font.pixelSize: sp(20)
            }
            AppImage {//giống thẻ Image của qml
                source: model.img_url//nếu đây là 1 web url thì sẽ lấy image asynchronous từ internet, load đc thì hiện
                width: parent.width
                height: model && width*model.img_height / model.img_width || 0
                //nếu có model thì thì sẽ tính toán kích thước height theo width đúng tỉ lệ ban đầu. Còn TH k tồn tại
                //thì or tức là lấy giá trị 0=>cách dùng && và || gán nhanh=>ảo là model trả ra có cả kích thước của model
                anchors.horizontalCenter: parent.horizontalCenter//????
            }
            AppText{
                text: "%1 bed, %2 bathrooms".arg(model.bedroom_number).arg(model.bathroom_number)//1 cách khác
                width: parent.width
                wrapMode: Text.WrapAtWordBoundaryOrAnywhere
            }
            AppText{
                text: model.summary
                width: parent.width
                wrapMode: Text.WrapAtWordBoundaryOrAnywhere
            }
        }
        ScrollIndicator {
            flickable: scroll
        }
        //của riêng Felgo dùng để set scroll cho AppFlickable
    }
}
