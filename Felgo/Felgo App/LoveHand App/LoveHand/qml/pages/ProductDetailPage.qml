import QtQuick 2.0
import Felgo 3.0

FlickablePage {
    useSafeArea: false
    title: "Chi tiết sản phẩm"
    property var model: ({})
    flickable.contentHeight: colProduct.height
    scrollIndicator.visible: true
    Column{
        id: colProduct
        width: parent.width
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.top: parent.top
        anchors.margins: contentPadding
        spacing: contentPadding
        AppText{
            color: "darkgreen"
            text: model.title.rendered
            font.bold: true
            x: parent.width/2 - width/2
        }
        AppImage{
            source: model.yoast_head_json.og_image[0].url
            fillMode: "PreserveAspectFit"
            width: parent.width
        }

        AppText{
            text: model.content.rendered
            wrapMode: Text.WrapAtWordBoundaryOrAnywhere
            width: parent.width
        }
    }
}
