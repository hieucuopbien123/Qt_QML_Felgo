import QtQuick 2.0
import Felgo 3.0

Page {
    id: page2
    readonly property int padding: dp(Theme.navigationBar.defaultBarItemPadding)
    useSafeArea: false
    title: "Page2"
    rightBarItem: NavigationBarRow{
        ActivityIndicatorBarItem{
            visible: true
            showItem: showItemAlways
            animating: true
        }
        IconButtonBarItem{
            icon: IconType.circleo
            title: "Title for icon circle"
            showItem: showItemIfRoom
            color: "red"
            onClicked: {
                console.log(navigationStack.depth)
                console.log(navigationStack.currentPage == page2)
                console.log(navigationStack.currentTitle)
            }
            iconSize: 50
        }
        IconButtonBarItem{
            icon: IconType.hearto
            title: "Title for icon heart"
            showItem: showItemNever
            color: Theme.navigationBar.itemColor//là mặc định theo màu OS
            onClicked: {
                console.log("Clicked")
            }
        }
    }
    Rectangle {
        width: 100
        height: 100
        color: "red"
        Behavior on width{
            NumberAnimation{
                duration: 1000
            }
        }
        MouseArea{
            anchors.fill: parent
            onClicked: {
                parent.width = 50
                console.log(navigation.currentNavigationItem.navigationStack.currentTitle)
            }
        }
    }
    AppButton{//thêm thoải mái các component khác theo thứ tự
        text: "Click"
        onClicked: {
            logic.testGet()
        }
        Connections{
            target: model
            onFinishFetching:{
                console.log(dataOfSignal)
            }
        }
    }
}
