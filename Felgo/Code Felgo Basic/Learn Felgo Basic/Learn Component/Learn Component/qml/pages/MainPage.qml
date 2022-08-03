import QtQuick 2.0
import Felgo 3.0

Page {
    Navigation{
        currentIndex: 2
        navigationMode: navigationModeTabs
        NavigationItem{
            icon: IconType.buysellads
            NavigationStack{
                DetailPage{}
            }
        }
        NavigationItem{
            icon: IconType.areachart
            NavigationStack{
                DetailPage2{}
            }
        }
        NavigationItem{
            icon: IconType.dashcube
            NavigationStack{
                DetailPage3{}
            }
        }
        NavigationItem{
            icon: IconType.weibo
            NavigationStack{
                DetailPage4{
                    onLogout: navigation.currentNavigationItem.navigationStack.popAllExceptFirst()
                }
            }
        }
    }
}
