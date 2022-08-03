import QtQuick 2.0
import Felgo 3.0
import QtQuick.Controls 2.4

Item {
    Rectangle {
        id: rectangle
        width: 567
        height: 448
        color: "green"
        SwipeView{
            id: swipe
            width: parent.width
            spacing: 400
            height: 400
            Item {
                AppText {
                    id: appText
                    text: qsTr("Helo wordl")
                }
            }

            Item {
                AppText {
                    id: appText1
                    text: qsTr("Hieu Nguyen")
                }
            }
        }
        PageIndicator{
            count: swipe.count
            currentIndex: swipe.currentIndex
            anchors.bottom: swipe.bottom
            anchors.horizontalCenter: swipe.horizontalCenter
        }
    }

}

/*##^##
Designer {
    D{i:0;autoSize:true;height:480;width:640}
}
##^##*/
