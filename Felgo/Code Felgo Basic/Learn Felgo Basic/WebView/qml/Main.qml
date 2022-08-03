import Felgo 3.0
import QtQuick 2.0
import QtWebView 1.1

import "./test2.js" as Hello
import "../JS/test.js" as Hello2
//file import ta thêm vào trong thư mục qml thì thư mục đó tự đc copy vào phần debug nên chạy đc luôn. Nếu ta dùng JS ra
//file riêng k nằm trong thư mục qml thì ta phải chủ động copy nó vào thư mục build thì mới ra được kq

App {
    NavigationStack {

        Page {
            title: qsTr("Main Page")

            Image {
                source: "../assets/felgo-logo.png"
                anchors.centerIn: parent
            }
            Text {
                id: web
                text: qsTr("text")
            }
            AppButton {
                anchors.centerIn: parent
                onClicked: {
                    console.log(Hello2.func())
                    crawler.requestToWebsite("https://lovehands.vn/")
                }
            }
        }
//        WebView{//webview và code C++ vân hoạt động với qt nhưng felgo live thì k
//            id: webview
//            visible: true
//            anchors.fill: parent
//            url: "https://www.google.com"
//        }
//        function getSource(){
//            var js = "document.documentElement.outerHTML";//outerHTML trả ra thẻ đó và con thẻ đó
//            webview.runJavaScript("document.title", function(result){
//                console.log("Run" + result);
//            })//chỉ chạy được runJavascript khi đối số 1 là code js chạy xong
//        }
    }
}
