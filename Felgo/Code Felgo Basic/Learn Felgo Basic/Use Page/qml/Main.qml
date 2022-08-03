import Felgo 3.0
import QtQuick 2.0
import "./pages"
import "./model"
App {
    //NavigationStack là cái chứa các Page, hiển thị ra ngoài là 1 thành hình chữ nhật đầu màn hình. Khi chứa page thì
    //page sẽ nằm dưới cái thanh đó và chiếm toàn bộ phần không gian còn lại. Chú ý kg ở đây giới hạn trong màn hình
    //của ta, chẳng qua content page bị in ra ngoài do các item bên trong kích thước lớn. Ta chỉnh kích thước bên trong
    //theo page và có thêm contentPadding la xong.
    //1 page trong 1 navigationStack khi set title cho page thì navigationStack chứa nó sẽ mang title đó
    //1 Page có thể lồng 1 page khác sẽ đè lên page cũ, 1 navigationStack lồng lên 1 navigationStack cx ok luôn
    //Tuy nhiên page lồng page với nav lồng nav chả để làm gì cả. Mà người ta sẽ cho nav lồng 1 page duy nhất
    //và dùng nhiều nav với Navigation + NavigationItem. Còn muôn nhiều page trong 1 nav thì sẽ thao tác với
    //các hàm pop và push thì page sẽ xếp theo trục z hiển thị và tự động có animation tùy vào hđh

    //Navigation sẽ giúp move qua lại giữa các nav stack còn navigation stack sẽ move qua lại các page trong stack
    //đó

    //hàm push sẽ thêm 1 page nx lên đầu stack X hàm pop sẽ bỏ page ở trên cùng của stack

    //khi 2 navstack lồng nhau
//    Item{
//        anchors.fill:parent
//        NavigationStack{
//            Page{
//                title: "adfsdf"
//                NavigationStack{
//                    Page {
//                      title: "Hello Felgo"

//                      AppText {
//                        anchors.centerIn: parent
//                        text: "Hi :)"
//                      }
//                    }
//                }
//            }
//        }
//    }

//    Item{
//        anchors.fill: parent
//        Page{
//            NavigationStack{
//                leftColumnIndex: 1
//                Page1{
//                }
//            }
//        }
//    }
    //leftColumnIndex là cái xác định firstPage là page thứ mấy. Nếu ta cho là 0 thì page số 0 là firstPage, tức
    //first page là cái Page1 thêm vào stack đầu tiên hiển thị ra ở bên trên. Còn nếu ta đặt firstPage là 1 thì cái
    //firstPage là page thứ 2 khi Page1 ta gọi push.
    //Quy tắc: mặc định firstPage là 0. Khi số page k chạm tới leftColumnIndex thì firstPage vẫn là 0.
    //Hàm push được gọi ở page nào của stack thì sẽ được push vào sau page đó của stack, nếu k được push vào sau
    //page đó thì sẽ lỗi.
    //Quy tắc 3 cho thầy hàm popAllExceptFirstAndPush k hữu dụng trong đa số trường hợp vì nếu ta pop thành công
    //1 page đồng nghĩa với vc cái page sẽ push thêm vào sẽ gây lỗi vì k được thêm vào sau page cần thêm sẽ lỗi
    //Tức là khi gọi popAllExceptFirstAndPush thì bản thân page đang gọi phải là firstPage
    //Tưởng vô dụng nhưng nó vẫn có ích trong 1 vài TH ta lỡ gọi cái gì trong hàm làm hàng loạt page được thêm vào
    //Xong có 1 option ta k muốn thêm các page đó nx mà muốn thêm 1 page khác, v thì gọi hàm này để pop hết các page
    //vừa mới thêm mà muốn xóa xong push page mới vô
    //Bth thì chỉ cần push, pop, popAllExceptFirst là đc
    //Ví dụ firstPage là 5 mà ta đang ở page 10 gọi popAllExceptFirst là về page 5 luôn

    //TH gọi popAllExceptFirst khi đang ở firstPage. Nếu ta đang ở firstPage thật và k có page nào đè lên mà gọi
    //hàm này sẽ bị lỗi mất tiêu đề. Nhưng nếu ta push 1 page xong gọi hàm này luôn thì sẽ k sao. Hãy cho nó
    //làm đúng vai trò của nó chứ nếu nó k pop gì cả thì bị lỗi mất tiêu đề đó. Nhưng lỗi này sẽ k xảy ra khi gọi
    //popAllExceptFirstAndPush vì push xong quay trở lại tiêu đề lại hiện ra thôi

    //Navigation là cái cột bên trái kéo ra kiểu drawer or tab. NavigationItem là từng hàng trong cột đó. Mỗi hàng
    //sẽ refer đến 1 item hiển thị ở cột bên phải trong splitView

    //=>Chốt: khi thêm bớt bth thì push và pop bth. Còn khi nào cần 1 cái firstPage để làm cj xong 1 phát về page đó
    //luôn thì mới đặt leftColumnIndex và dùng 2 hàm kia

//    Item{
//         anchors.fill: parent
//        Page{
//            Navigation{
//                NavigationItem{
//                    NavigationStack{
//                        Page1{
//                        }
//                    }
//                }
//            }
//        }
//    }

    //TH tạo vòng lặp page 1 push page 2, xong page2 push page 1 là sai và bị lỗi.Vì content của 1 page nằm trong
    //cái còn lại mà


    Model{
        id: model
        dispatcher: logic
    }

    Logic{
        id: logic
    }

    AppButton{
        text: "Click"
        onClicked: {
            logic.getVoice();
        }
    }
}
