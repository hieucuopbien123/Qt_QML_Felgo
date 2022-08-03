import QtQuick 2.12
import QtQuick.Window 2.12
import QtQuick.Controls 2.12

Window {
    width: 640
    height: 480
    visible: true
    title: qsTr("Hello World")
    id: root

    Row{
        id: tools

        Button{
            id: clear
            text: "Clear"
            onClicked: {
                canvas.clear()
            }
        }

        Button{
            id: save
            text: "Save"
            onClicked: {
                mouse.save()
            }
        }
    }
    Canvas{//biến lưu context là màn hình vẽ
        id: canvas
        anchors.top: tools.bottom
        width: 500
        height: 500
        property int lastX: 0
        property int lastY: 0

        //mỗi cái class như này là 1 biến với type đã đc xác định sẵn ở đây là canvas và tên chính là id
        //ta có thể khai báo 1 function cho nó như này r gọi canvas.clear() để dùng hàm
        function clear() {
            var ctx = getContext("2d")
            //khai báo biến kp là thuộc tính để lấy cái gì ra dùng, var lưu mọi kiểu và ở đây là kiểu Context2D: object
            //hàm getContext của canvas lấy cái context đang vẽ lên của canvas, canvas chỉ support 2d context thôi
            ctx.reset()//hàm reset cái context sẽ xóa mọi thứ trên context thành trống, các biến khác về default
            canvas.requestPaint()//requestPaint sau reset để thực hiện reset->reset đứng 1 mình k phát signal paint để vẽ
            mouse.clear()//mouse từ class C++ trở thành 1 thuộc tính của file qml, gọi hàm thoải mái

            if(lastX == 0)//dùng được ss như bth
            {
                console.assert(lastX == 0, "This will pass");//console có các hàm phục vụ debug
                console.log("Last x is ", lastX, " and last y is ", lastY);
            }
        }

        //onPaint là slot khi phát ra signal paint,onPaint kết thúc nó cx phát ra signal painted r thực hiện slot onPainted
        //có 2 hàm markdirty() mà requestPaint() sẽ phát signal paint để gọi hàm này
        onPaint: {
            //context lưu cái context của canvas là biến quan trọng để vẽ lên canvas. Ta có thể điều chỉnh thuộc tính or gọi
            //hàm thoải mái như thế này
            var ctx = getContext("2d")
            ctx.lineWidth = 2
            ctx.strokeStyle = "red"
            ctx.beginPath()//reset current path to new path

            //các hàm vẽ
            ctx.moveTo(lastX, lastY)//set current là vị trí này
            lastX = area.mouseX
            lastY = area.mouseY
            ctx.lineTo(lastX, lastY)
//            ctx.lineTo(lastX-16, lastY-7)//draw a line từ current đến vị trí này
//            ctx.lineTo(lastX+10, lastY+10)
//            ctx.lineTo(lastX+1, lastY+1)

//            ctx.closePath()
            ctx.stroke()//stroke là đường viền, nét
            //đây là hàm cuối cùng bảo là vẽ lên các thứ đã set vào biến context2d bên trên

            mouse.test()
            mouse.add(lastX, lastY)
            mouse.add(Qt.point(lastX, lastY))
            //Qt là 1 global object cung các enum và function hưu ích, ví dụ lấy point từ 2 điểm như trên
        }
        //hàm onPaint làm nv vẽ lên canvas cái gì. Ở đây nó được gọi mỗi khi requestPaint phát ra.
        //Tức là ở đây ta set mỗi khi chuột pressed và vị trí đổi

        MouseArea{
            id: area
            anchors.fill: parent
            onPressed: {//tương tự đây chỉ là slot cho signal pressed, chỉ phát ra mỗi khi nhấn chuột vào k gian
                canvas.lastX = mouseX//mouseX, mousey là thuộc tính của MouseArea
                canvas.lastY = mouseY
		//Chú ý là trong qml, dùng cái gì của cha trong con thì phải thêm id vì trong con thì chỉ dùng đc TT các
                //thuộc tính của con mà thôi

                //Invalid write to global property "lastX" => lỗi phổ biến này xuất hiện khi ta write vào 1 property tự khai
                //báo ở cha. Điều này là sai mà phải thêm id đăng trước
                //Khi cha con có property cùng tên thì dùng con trực tiêp, dùng cha phải có id
            }
            onPositionChanged: {
//                canvas.lastX = mouseX
//                canvas.lastY = mouseY
                canvas.requestPaint()
            }
            //là handler của signal positionChanged, nó phát ra khi chuột thay đổi vị trí và được pressed ở
            //trong vùng không gian mouseArea đang xét.
        }
    }
}
//quy trình: đầu tiên ấn chuột trong canvas thì phát onPressed nên lastX và lastY sẽ lấy vị trí con chuột->di chuột đi 1 tẹo
//thì gặp onPositionChanged sẽ chạy onPaint-> trong onPaint nó set bắt đầu vẽ 1 path mới-> set điểm đầu là lastX, lastY là
//vị trí con chuột lúc bắt đầu click và gọi lineTo và set điểm cuối của đth là vị trí con chuột hiện tại sau khi dịch r gọi
//stroke để vẽ đth cực ngắn đó(do đường thẳng quá ngắn vì signal phát liên tục nên ta k thấy là vẽ 1 đường thẳng)->sau đó rê
//thêm 1 đoạn cực ngắn nx thì lại begin 1 path mới->điểm đầu là cái mouseX, mouseY ta set từ trước, điểm cuối là vị trí sau
//khi rê cực ngắn->stroke để tô lên. Cứ như v đến khi tô hết đường thẳng

//có path và bên trong path có subpath. hàm beginpath sẽ bắt đầu 1 cái path mới bằng cách khiến cho biến context của canvas
//k còn dính dáng gì đến cái path và subpath cũ. Sau khi beginpath, gọi moveTo(x,y) sẽ tạo ra 1 subPath mới tại điểm (x,y)
//của path hiện tại. Những đường path là những đường vô hình do ta tạo ra, sau khi ta fill nó or stroke cái path đó bằng màu
//thì ta mới nhìn thấy nó trên canvas.
//Như v cái begin path có vai trò gì, rõ ràng ta chỉ cần set điểm đầu điểm cuối r vẽ 1 đth từ đầu đến cuối là 1 khoảng cực
//ngắn như v là xong, nhưng có sự khác biệt giữa 1 path và 1 subpath => giả sử bỏ begin path tức là cả Ct ta chỉ dùng ! 1
//đường path và vô số đường subpath bên trong. Nên nhớ là các đường subpath sẽ có mỗi liên hệ với nhau gọi là điểm join. Khi
//các subpath giao nhau thì điểm join sẽ đè lên nhau theo các style như bevel/round/miter join khiến cho đường chéo bị đậm
//lên vì bản chất vẽ 1 đường chéo là vẽ lên từ những đường ngang dọc kế tiếp nhau cực kỳ nhỏ làm cho ta nhìn thấy đường chéo.
//Các đường chéo ta vẽ, sẽ cố thêm các chi tiết vào để tạo ra cái kiểu style join làm cho nó đậm hơn, kiểu gì nó cũng sẽ đậm
//hơn 1 nét path bth. Do đó vẽ đường chéo thì nó bị đậm hơn, còn vẽ đường ngang dọc thì nhạt. Nhưng các path thì lại k có qh
//j với nhau dẫn đến nếu ta làm như trên tức mỗi 1 đường cực nhỏ đều là 1 path chứ kp subpath thì nét vẽ sẽ trơn tru dù là
//đường chéo hay ngang dọc

//hàm closePath sẽ close cái subpath bằng cách vẽ 1 đường tới điểm đầu subpath và bắt đầu 1 path mới. Tức là begin path là
//bắt đầu 1 path mới trong khi closepath sẽ vẽ thêm 1 đường thẳng từ đầu tới cuối r ms bắt đầu 1 path mới. Điều đb là nó vẽ
//quá vị trí đầu cuối 1 chút. Để thấy đc hiệu ứng của nó có thể bỏ begin path, ctx.lineTo(lastX-16, lastY-7), closepath,
//bỏ moveTo, closePath dùng vào vc khác ta chưa học vội

//Tìm hiểu thêm: -nhét hàm trong onPressed vào trong onPositionChanged-> k vẽ ra j cả vì điểm đầu điểm cuối luôn trùng nhau
//-Tiếp đó thử cho điểm cuối=điểm đầu+1 sẽ vẽ ra nhưng dấu chấm vì mỗi lần gọi stroke chỉ vẽ lên 1 pixel từ vị trí hiện tại
//-Ban đầu, nếu dùng cuối=đầu+10 luôn thì sẽ dẫn đến hàm xóa bị thừa nét cuối và đường vẽ bị gián đoạn thành những đường
//thẳng->là bởi vì điểm cuối bị set xuống dưới sang phải 10px nên k còn vẽ đth cực ngắn nx mà là 1 đth từ vị trí bđ đến vị
//trí hiện tại+10px. Nó khiến ta nhìn rõ tính chất vẽ đường thẳng của hàm lineTo(x,y). signal positionChanged phát ra theo
//khoảng thời gian nhất định sau khi di chuột, nên nếu ta di chuột nhanh hay chậm sẽ có được mouseX, mouseY vị trí khác nhau
//Nếu để như ban đầu và vẽ những hình tròn với tốc độ cao thì do cơ chế vẽ các đường thẳng ở điểm đầu và điểm cuối nên khi
//tốc độ cao thì điểm đầu và điểm cuối xa nhau nên ta k thể vẽ được các đường cong của hình tròn mà nó sẽ thành hình đa giác
//với các đường thẳng. Còn để +10px ở điểm cuối sẽ vẽ ra các đường thẳng bị rời rạc bởi vì nó vẽ các path liên tục nhưng
//điểm đầu k trùng điểm cuối nên bị rời ra do điểm cuối cũ quá 10px so với điểm đầu mới

//Các bc: lấy context + set nét bút->set điểm đầu->set vẽ kiểu gì tới điểm cuối->tùy tình huống mà có dùng các hàm begin hay
//close path tức cần các đường k đè nhau or cần vẽ 1 dth từ đầu tới cuối không
