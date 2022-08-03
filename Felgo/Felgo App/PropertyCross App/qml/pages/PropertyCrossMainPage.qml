import QtQuick 2.0
import Felgo 3.0
import VPlayApps 1.0

Page {
    //readonly dùng khi k muốn đổi thuộc tính nào trong app
    //ta phải khai báo 1 vài default như contentPadding là space giữa lề và app
    //dp là device pixel là hàm sẽ bỏ qua resolution của device và lấy khoảng cách giống nhau với mọi device để giải
    //quyết vấn đề nhiều thiết bị có high solution và low solution thì vị trí nó khác nhau
    readonly property real contentPadding: dp(Theme.navigationBar.defaultBarItemPadding)//cái này cx là hso = 15 thôi
    //cái contentPadding này dùng cho các vị trí Page hiển thị nên các các lề màn hình 1 khoảng là contentPadding
    //chứ k nên sát hẳn màn hình
    //navigation bar là cái thanh ngang đầu app ấy
    //ta thg kiểu viết code giả định thuộc tính tồn tại trc r mới viết thuộc tính đó sau
    property alias childNavigationStack: navStack
    //alias là cái kiểu biến ref tới 1 property khác, chỉ là ta dùng đc cái tên khác
    //biến này có vai trò track theo sự thay đổi của navigation stack, thay đổi như nào nó sẽ bắt đc và sử dụng bên ngoài
    //VD dùng google analytic là plugin felgo hỗ trợ cần biết navigation stack đổi như thế nào để hiển thị chẳng hạn
    useSafeArea: false //thuộc tính của page giúp nó dùng toàn màn hình, nếu k nó chỉ dùng ở các vùng trống an toàn

    //Vc move giữa các page thật ra là add thêm page mới or remove page đi
    NavigationStack {//1 page có stack chứa nhiều page
        id: navStack
        leftColumnIndex: 1
        splitView: tablet&&landscape //dùng split view(cái open document của qt,ấn vào gì thì chuyển view sang file khác)
        //tức set chỉ dùng splitView trên thiết bị tablet ở chế độ landscpae
        SearchPage {}
    }
}
