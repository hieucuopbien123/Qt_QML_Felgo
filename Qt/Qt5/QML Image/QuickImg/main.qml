import QtQuick 2.12
import QtQuick.Window 2.12
import QtQuick.Controls 2.0
//vẫn nên dùng qt5 hơn qt 6 nh chỗ xấu vl

Window {
    //window nếu k set kích thước thì nó khá nhỏ khi hiển thị, set thì nó theo ta hiển thị ra lúc ban đầu
    //nhưng kích thước width, height của window sẽ tự động resize khi ta phóng to cửa sổ->chú ý nó ảnh hưởng đến
    //kích thước các con bên trong khi set theo kích thước của window
    width: 500
    height: 500
    visible: true
    title: qsTr("Hello World")
    id: root//chú ý là id k đc viêt hoa

    Column {
        //kích thước width height luôn mặc định là 0. Khi ta additem vào nó mới tự rộng ra để vừa
        //2 cái Column và row k kiểm soát đc chiều dài, cứ bnh Item thì dài nv thôi. Ta mới chỉ quan tâm là
        //nó cho phép sắp xếp theo hàng or cột và chiều đài nó theo chiều dài item->v thôi. Học layout sau
        //Nếu window kích thước nhỏ k thấy thì ta resize nó bằng chuột để nhìn full
        Row{
            id: tools
            spacing: 2
            Button {
                text: "Reset"
                onClicked: {
                    //fillMode là 1 enum(lấy enum trong class qml bằng: type.<tên thuộc tính enum>) giúp ta xác định
                    //render ntn khi mà ảnh có kích thước khác với cái phạm vi object. Ví dụ ta muốn render 1 bức ảnh
                    //nhưng k thể lúc nào render cx cho kích thước full đc, khi đó ta set width height k đúng cho object
                    //thành ra phải dùng fillMode để quyết định ảnh in thiếu, co dãn or cut or giữ nguyên dữ liệu
                    display.fillMode = Image.Stretch
                    //sourceSize mang kích thước full chuẩn của sourceSize(QSize)
                    display.width = display.sourceSize.width
                    display.height = display.sourceSize.height
                    display.anchors.centerIn = viewport
                    display.clip = false//cho phép ảnh được phép cắt mất dữ liệu hay k
                }
            }
            Button {
                text: "Strech"
                onClicked: {
                    //Stretch là ảnh được phép scale để hiển thị toàn bộ dữ liệu theo width height.
                    display.fillMode = Image.Stretch
                    display.width = 200
                    display.height = 25
                }
            }
            Button {
                text: "Preserve Aspect Fit"
                onClicked: {
                    //tương tự stretch nhưng đảm bảo k méo, nó vẫn sẽ thu nhỏ hay phóng to tùy width height ntn
                    display.fillMode = Image.PreserveAspectFit
                    display.width = 800
                    display.height = 200
                }
            }
            Button {
                text: "Preserve Aspect Crop"
                onClicked: {
                    //tương tự PreserveAspectFit nhưng nó cắt để vừa chứ k giữ
                    display.fillMode = Image.PreserveAspectCrop
                    display.width = 25
                    display.height = 400
                    display.clip = false//false k đc nó ép cắt ở fillMode r
                }
            }
            Button {
                text: "Tile"
                onClicked: {
                    display.fillMode = Image.Tile//nhân bản 2 chiều, k méo nhưng 1 chiều có thể méo
                    display.width = viewport.width
                    display.height = viewport.height
                }
            }
            Button {
                text: "Tile Horizontally"
                onClicked: {
                    display.fillMode = Image.TileHorizontally
                    display.width = viewport.width
                    display.height = viewport.height
                }
            }
            Button {
                text: "Tile Vertically"
                onClicked: {
                    display.fillMode = Image.TileVertically
                    display.width = viewport.width
                    display.height = viewport.height
                }
            }
        }
        Rectangle {
            id: viewport
            width: root.width//cho đổi theo kích thước window khi resize
            height: root.height
            AnimatedImage{
                id: display
                anchors.centerIn: parent
                source: "/img/img/banana.gif"
            }
        }
    }
}
//chú ý cái gì hiển thị mà k có sẵn chiều dài thì phải specific width, height cho nó vì sẽ hiện là 0 hết chả thấy gì
//cả (VD ảnh thì load phát là lấy kích thước ảnh nếu chưa set thì lấy chuẩn, còn hcn thì chả có cj ban đầu mặc định
//là width=height=0)
//dùng id hay ở chỗ ta khai báo object BẤT CỨ ĐÂU đều có thể lấy được thuộc tính của nó ra dùng vc dùng id như thế
//thì nó là vị trí render lên đối tượng đó là cố định, nếu là con thì mới đổi dính liền với object cha
