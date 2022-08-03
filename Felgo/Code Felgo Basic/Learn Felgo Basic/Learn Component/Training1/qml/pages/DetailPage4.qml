import QtQuick 2.0
import Felgo 3.0

//K đặt tên đc là DetailPage3
Page {
    useSafeArea: true
    title: "Page 3"
    Column{
        anchors.centerIn: parent
        Row{
            AppText{//AppText có chữ chuẩn hơn text
                width: 200
                text: "Component 1"
                wrapMode: Text.WrapAtWordBoundaryOrAnywhere
                font.italic: true
                font.bold: true
                font.family: "Helvetica"
                horizontalAlignment: Qt.AlignHCenter
            }
            AppText{
                text: "Component 2"
            }
        }
        Row{
            AppText{
                text: "Component 3"
            }
            AppText{
                text: "Component 4"
            }
        }
    }
}
