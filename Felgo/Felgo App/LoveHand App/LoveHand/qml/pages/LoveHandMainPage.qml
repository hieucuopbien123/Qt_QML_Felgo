import QtQuick 2.0
import Felgo 3.0

Page {
    readonly property real contentPadding: dp(Theme.navigationBar.defaultBarItemPadding)
    Navigation {
        id: navigation
        currentIndex: 0
        headerView: AppImage {
             id: drawerImage
             width: parent.width
             source: "../../assets/logo.jpg"
             fillMode: AppImage.PreserveAspectFit
        }


        NavigationItem {
            id: navigationItem3
            title: "Trang chủ"
            icon: IconType.home
            NavigationStack {
                id: navigationStack3
                MainPage {
                }
            }
        }

        NavigationItem {
            id: navigationItem
            title: "Giới thiệu"
            icon: IconType.smileo
            NavigationStack {
                id: navigationStack
                IntroPage {
                    id: introPage
                }
            }
        }

        NavigationItem {
            id: navigationItem1
            title: "Sản phẩm"
            icon: IconType.cartplus
            NavigationStack{
                ProductPage{
                }
            }
        }
//        NavigationItem {
//            id: navigationItem2
//            title: "Kiến thức"
//            icon: IconType.lightbulbo
//            NavigationStack{
//                ListBlogPage{
//                }
//            }
//        }
//        NavigationItem {
//            id: navigationItem3
//            icon: IconType.ambulance
//            title: "Phòng - Chữa bệnh"
//            NavigationStack{

//            }
//        }
        NavigationItem {
            id: navigationItem2
            title: "Blog"
            icon: IconType.lightbulbo
            NavigationStack{
                ListBlogPage{
                }
            }
        }
        NavigationItem {
            id: navigationItem4
            title: "Tìm kiếm"
            icon: IconType.question
            NavigationStack{
                SearchPage{}
            }
        }
        NavigationItem {
            id: navigationItem5
            title: "Liên hệ"
            icon: IconType.phone
            NavigationStack{
                ContactPage{
                }
            }
        }
//        NavigationItem {
//            id: navigationItem6
//            title: "Cài đặt"
//            icon: IconType.gear
//            NavigationStack{
//                SettingPage{
//                }
//            }
//        }
    }


}
