import QtQuick 2.0
import Felgo 3.0

FlickablePage {
    property var titleParam: ""
    property var contentParam: ""
    flickable.contentHeight: text.height
    scrollIndicator.visible: true
    property var isFavourite: dataModel.isFavourite(titleParam)
    title: qsTr("%1").arg(titleParam)//k đc gán trực tiếp khi bind title mà phải như này
    rightBarItem: IconButtonBarItem{
        icon: isFavourite ? IconType.heart : IconType.hearto
        onClicked: {
            logic.toggleFavourite(titleParam,contentParam)
            console.log("Length: " + dataModel.favouriteList.length)
        }
    }

    function handleContent(content){
        var count = 0;
        while(content.indexOf('\" />') > 0){
            var to = content.indexOf('\" />') + 4;
            var from = content.indexOf("width")

            console.log(from)
            console.log(to);
            content = content.slice(0,from) + content.slice(to);
            count++;
            if(count === 10) break;
        }
        while(content.indexOf('\"/>') > 0){
            var to = content.indexOf('\"/>') + 3;
            var from = content.indexOf("class")

            console.log(from)
            console.log(to);
            content = content.slice(0,from) + content.slice(to);
            count++;
            if(count === 10) break;
        }
        return content;
        //chú ý text của AppText bind với contentParam. Nếu contentParam bị thay đổi trong hàm này nó lại gọi lại
        //hàm này để gán cho text của AppText, cứ thế tạo lỗi bind loop
    }

    AppText{
        id: text
        text: handleContent(contentParam)
        wrapMode: Text.WrapAtWordBoundaryOrAnywhere
        anchors.top: parent.top
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.margins: contentPadding
    }
}
