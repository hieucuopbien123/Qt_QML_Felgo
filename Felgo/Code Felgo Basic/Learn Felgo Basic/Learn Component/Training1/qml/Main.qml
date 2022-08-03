import Felgo 3.0
import QtQuick 2.0

App {
    Component.onCompleted: {
        settings.setValue("Name","Hieu")
        dpScale = 1
        keyboardVisible = true
        shutdownAppWithEscapeKeyEnabled = false
        console.log(diameterInInches,dpScale,heightInInches,keyboardHeight,keyboardVisible,
                    licenseKey,isOnline,landscape, portrait, screenHeight,settings.getValue("Name"))
        console.log(spScale,shutdownAppWithEscapeKeyEnabled)
        HttpNetworkActivityIndicator.activationDelay = 0
        var loading = HttpNetworkActivityIndicator.enabled
        //các thuộc tính màn hình này nó thay đổi tùy theo loại
        //điện thoại nên dùng nó cho chuẩn hơn là fix cố định
        //landscape mode được bật khi width > height  X  portrait mode
        //dpScale là dp() value mà giá trị bên trong được nhân với, mặc định là 1
        //các thuộc tính kp readonly ta có thể thay đổi điều khiển app
        //VD set dpScale=2 phát là tự dưng các component trên điện thoại trở nên to đùng
        //chú ý là thuộc tính keyboardVisible kiểm tra xem hiện tại keyboard có hiện ra hay k
        //mặc dù kp readonly nhưng ta thay đổi nó là true thì keyboard cx k hiện ra đâu nhé
        //cái này chỉ để check thôi, k động vào
        //settings sẽ lưu data theo kiểu key-pair trong database trên máy gọi là SQLite
    }

    MainItem{
        anchors.fill: parent
    }
    //Chú ý nếu ta làm mà k set Item fill cái App thì hiển thị sai mnl, mỗi lần dùng component ở file khác
    //ta tạo ra thì phải chú ý vị trí của nó với file này nhé
}
