import QtQuick.Controls 2.5
import QtQuick 2.12

Item {
    //    id: iditem1 //có id ở item là lỗi nhé
    clip: false
    width: 400
    height: 400

    Column {
        id: column
        width: parent.width
        Row {
            id: row
            width: parent.width
            anchors.top: parent.top

            //            Button {
            //                id: button
            //                width: row.width / 2
            //                text: qsTr("This is a button")
            //                anchors.left: parent.left
            //                anchors.leftMargin: 0
            //            }
            //BH nó cấm cả Button luôn, tốt nhất chuyển hoàn toàn qua Design Studio
            Text {
                id: text1
                width: row.width / 2
                height: button.height
                text: qsTr("Content")
                anchors.left: button.right
                font.pixelSize: 12
                horizontalAlignment: Text.AlignHCenter
                verticalAlignment: Text.AlignVCenter
                anchors.leftMargin: 0
            }
            layoutDirection: Qt.LeftToRight
            spacing: 77
            transformOrigin: Item.Center
            anchors.topMargin: 0
        }
        Image {
            id: image
            width: 505
            height: 360
            source: "img/img/t2.jpg"
            fillMode: Image.PreserveAspectFit
            anchors.horizontalCenter: row.horizontalCenter
            anchors.topMargin: text1.height
        }
    }
}

/*##^##
Designer {
    D{i:0;formeditorZoom:0.9}
}
##^##*/

