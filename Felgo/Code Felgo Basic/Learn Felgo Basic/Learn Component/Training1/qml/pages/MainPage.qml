import QtQuick 2.0
import Felgo 3.0

Page {
    Navigation{
        id: navigation
        Component.onCompleted: {
            console.log(navigation.currentIndex)
            console.log("Load xong navigation")
            currentIndex = 9// open second nav
            //nó load hết các thứ bên trong thì mới coi là load xong navigation bên ngoài
            //nhưng đặc biệt là thuộc tính currentNavigationItem sẽ là null ở đây vì nó chưa chạy, thuộc
            //tính này chỉ có thể dùng đc về sau khi xong hết r=> vẫn lấy đc currentIndex
        }
        enabled: true
        NavigationItem{
            Component.onCompleted: {
                console.log("Load xong item trong navigation")
            }
            title: "tab1"
            icon: IconType.heartbeat
            NavigationStack{
                Component.onCompleted: {
                    console.log("Load xong navigation stack")
                }

                DetailPage{
                    id: page1
                    Component.onCompleted: {
                        console.log("Load xong page")
                    }
                }
            }
        }
        NavigationItem{
            enabled: true
            icon: IconType.angellist
            NavigationStack{
                leftColumnIndex: 1//vị trí ở phía bên trái khi dùng đến splitView
                splitView: tablet
                initialPage: DetailPage2{
                    id: page2
                }
            }
        }
        NavigationItem{
            enabled: true
            icon: IconType.adjust
            NavigationStack{
                MainPageList{
                }
            }
        }
        NavigationItem{
            enabled: true
            icon: IconType.adn
            NavigationStack{
                splitView: tablet
                initialPage: DetailPage4{
                    id: page3
                }
            }
        }
        NavigationItem{
            enabled: true
            icon: IconType.ambulance
            NavigationStack{
                splitView: tablet
                initialPage: DetailPage5{
                    id: page5
                }
            }
        }
        NavigationItem{
            enabled: true
            icon: IconType.lifesaver
            NavigationStack{
                splitView: tablet
                initialPage: DetailPage7{
                    id: page6
                }
            }
        }
        NavigationItem{
            enabled: true
            icon: IconType.aligncenter
            NavigationStack{
                splitView: tablet
                initialPage: Page{
                    AppListView{
                        delegate: SimpleRow {}
                           model: [
                             { text: "Widget test",
                               detailText: "Some of the widgets available in Felgo AppSDK",
                               icon: IconType.tablet },
                             { text: "Shown are:",
                               detailText: "ListPage, NavigationBar with different items, Switch",
                               icon: IconType.question }
                           ]
                    }
                }
            }
            //Chú ý navigation stack phải có Page, nếu k nó sẽ tính từ mốc 0,0 trên cùng và thanh stack sẽ
            //đè component
            //AppListView giống ListPage nhưng thật ra ListPage thì hiển thị 1 danh sách các Page, còn AppListView
            //kiểu hiển thị thông tin để nhìn thấy thôi, khi click vào thì k mở 1 page mới. Ta hoàn toàn có thể
            //dùng được tùy ý nhưng nên dùng đúng theo công dụng như v
        }
        NavigationItem{
            enabled: true
            icon: IconType.angledoubledown
            NavigationStack{
                splitView: tablet
                initialPage: DetailPage8{
                    id: page8
                }
            }
        }
        NavigationItem{
            enabled: true
            icon: IconType.at
            NavigationStack{
                splitView: tablet
                initialPage: DetailPage9{
                    id: page9
                }
            }
        }
        NavigationItem{
            enabled: true
            icon: IconType.bank
            NavigationStack{
                splitView: tablet
                initialPage: DetailPage10{
                    id: page10
                }
            }
        }
    }
}
