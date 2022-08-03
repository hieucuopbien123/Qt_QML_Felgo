import QtQuick 2.0
import Felgo 3.0

Page {
    useSafeArea: false
    AppCard{
//        AppCardSwipeArea{//Chỉ vùng area của AppCard bị swipe, cx có thể dùng trong AppPaper
//            rotationFactor: 0.05
//            onSwipedOut: {
//                console.log("Card swipe out: " + direction)//direction của App card
//            }
//        }
        //Để swipe được cái AppCard thì phải đặt swipeEnabled true và cardSwipeArea sẽ tự truy cập vào
        //Component con AppCardSwipeArea của AppCard để ta chỉnh sửa. Or nếu k dùng cái có sẵn đó thì
        //tạo 1 Component mới như trên nhưng cách này k tốt vì ngầm định bên trong AppCard có 2 cái SwipeArea
        //1 cái enabled false, 1 cái ta tạo bên trong như trên.

//        swipeEnabled: true
//        cardSwipeArea.rotationFactor: 0.1
//        //default là 0.1 -> nó điều khiển vị trí của tâm quay và tốc độ swipe, càng lớn
//        //tâm càng dịch lên và tốc độ càng nhanh
//        cardSwipeArea.onSwipedOut: {
//            console.log("Card swipe out: " + direction)
//            //Ở trong đây dùng được các thuộc tính của AppCardSwipeArea của AppCard trực tiếp
//            //Còn nếu muốn dùng các thuộc tính của AppCard thì phải thông qua id=> chú ý là trong phạm vi
//            //Component nào thì chỉ dùng đc các attr component đó nhưng thuộc tính alias trỏ vào component khác
//            //thì trong phạm vi dùng alias đó chỉ dùng tt được attr component đó
//        }

        swipeEnabled: true
        cardSwipeArea {//các thuộc tính kiểu này thg là readonly
            rotationFactor: 0.1
            onSwipedOut: {
                console.log("Card swiped out: " + direction)
            }
            //signal phát ra khi card được swipe out, chỉ khi nó xác định hành động
            //swipe là valid. Khi kết thúc sẽ phát thêm onSwipedOutCompleted
            //còn có medthod swipeOut(direction) cx phát signal này
        }

        id: card
        width: parent.width
        margin: dp(20)
        paper.radius: dp(20)//AppPaper có sẵn của card

        header: SimpleRow{
            imageSource: "file:///B:/Qt/FelgoNew/Training1/Training1/assets/felgo-logo.png"
            text: "Lorem ipsum"
            detailText: "Ut enum ad minim veniam"
            enabled: false
            image {
                radius: image.width/2
                fillMode: Image.PreserveAspectCrop
                border.width: dp(1)
                border.color: "lightgrey"
            }
            //Chú ý các thuộc tính của Component là readonly thì khi muốn chỉnh sửa phải bỏ dấu ba chấm
            //Điều này chỉ đúng với các thuộc tính kiểu image như bên trên. VD image.fillMode
            //thì ta dùng image {fillMode:<>} => Ta kb rõ cái nào là readonly nên cứ chạy nếu debug gặp
            //thì nó sẽ báo lỗi readonly dùng như trên
            style: StyleSimpleRow{
                showDisclosure: true
                disclosureColor: "red"
                //cái disclosure là mũi tên > trỏ sang việc ấn sẽ làm gì
                //mặc định là true trong iOS=> nhưng cái này chỉ có trong kiểu chọn đc row ví dụ listpage thôi
                backgroundColor: "transparent"
            }
        }
        media: AppImage{
            width: parent.width
            fillMode: Image.PreserveAspectFit
            source: "../../assets/felgo-logo.png"
        }
        content: AppText{
            width: parent.width
            padding: dp(15)
            text: "Lorem ipsum dolor sit amet, consectetur adipiscing elit, sed do eiusmod tempor incididunt ut\
                   labore et dolore magna aliqua, Ut enim ad minim veniam, quis nostrud exercitation ullamco\
                   laboris nisi ut aliquip ex ea cimodo consequat"
        }
        actions: Row{
            IconButton{
                icon: IconType.thumbsup
            }

            IconButton{
                icon: IconType.sharealt
            }
            AppButton{
                text: "Follow"
                flat: true
            }
        }
    }
}
