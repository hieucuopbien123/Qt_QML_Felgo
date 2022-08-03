import QtQuick 2.12
import QtQuick.Window 2.12
import QtQuick.Controls 2.12

Window {
    width: 640
    height: 480
    visible: true
    title: qsTr("Hello World")
    id: root

    Column{
        id: cols
        anchors.fill: parent
        anchors.margins: 5
        spacing: 3

        Rectangle{
            id: frame
            width: parent.width
            height: 25
            border.color: "gray"
            border.width: 1//rectangle màu trắng mà k set gì cho border sẽ k hiện ra gì cả
            TextInput{
                id: textPlain
                anchors.fill: parent
                anchors.margins: 4
                selectByMouse: true
                onTextChanged: {//làm như này gõ có thể tràn ra ngoài khung
                    txtArea.text = Qt.btoa(textPlain.text)
                    //base64 encode với hàm btoa(), nó là kiểu mã hóa ở url đằng sau phần querry là dãy dài base64 encoded
                }
            }
        }


        Rectangle{
            id: frame2
            width: parent.width
            height: parent.height - frame.height - cols.spacing
            border.color: "gray"
            border.width: 1

            //dùng ScrollView
            /*ScrollView {
                id: view
                anchors.fill: parent//để như này vì quá phạm vi parent là hcn thì sẽ xuất hiện thanh bar
                TextArea {//thế thành textEdit cx đc
                    id: txtArea
                    width: 500
                    height: 500
                    selectByMouse: true
                    text: "<b>T</b>extArea\n...\n...\n...\n...\n...\n...\n"//html k hiển thị nhé
                    font.family: "Helvetica"
                    font.pointSize: 20
                    color: "blue"
                    wrapMode: TextEdit.Wrap//chế độ wrap là tự xuống dòng khi tràn dòng->k có scrollbar ngang
                }
            }*/

            //dùng Flickable
            /*Flickable{
                width: parent.width; height: parent.height;//có thể viết trên cùng 1 dòng với dấu ;
//                contentWidth: txtArea.width
//                contentHeight: txtArea.height
                contentWidth: contentItem.childrenRect.width; contentHeight: contentItem.childrenRect.height
                //contentItem lưu item bao cái item bị flick bên trong
                clip: true//kéo quá phạm vi k bị đè, nên luôn luôn để là true
                TextArea {
                    id: txtArea
//                    selectByMouse: true
                    text: "<b>T</b>extArea\n...\n...\n...\n...\n...\n...\n"//html k hiển thị nhé
                    font.family: "Helvetica"
                    font.pointSize: 20
                    color: "blue"
                    wrapMode: TextEdit.Wrap
                }
            }*/

            //Flickable bao ScrollView->k nên
            /*Flickable{
                width: parent.width; height: parent.height;
                contentWidth: contentItem.childrenRect.width; contentHeight: contentItem.childrenRect.height
                clip: true
                ScrollView {
                    id: view
                    width: 500
                    height: 1000
                    contentWidth: contentItem.childrenRect.width; contentHeight: contentItem.childrenRect.height
                    clip: false
                    TextArea {
                        id: txtArea
                        text: "<b>T</b>extArea\n...\n...\n...\n...\n...\n...\n"
                        font.family: "Helvetica"
                        font.pointSize: 20
                        color: "blue"
                        wrapMode: TextEdit.Wrap
                    }
                }
            }*/

            //scrollView bao Flickable->k nên
            /*ScrollView {
                id: view
                anchors.fill: parent
                Flickable{
                    width: parent.width; height: parent.height;
                    contentWidth: contentItem.childrenRect.width; contentHeight: contentItem.childrenRect.height
                    clip: true
                    TextArea {
                        id: txtArea
                        text: "<b>T</b>extArea\n...\n...\n...\n...\n...\n...\n"
                        font.family: "Helvetica"
                        font.pointSize: 20
                        color: "blue"
                        wrapMode: TextEdit.Wrap
                    }
                }
            }*/

            //xem hoàn chỉnh
            Flickable {
                id: flickable
                anchors.fill: parent
                boundsMovement: Flickable.StopAtBounds//or boundsBehavior

                TextArea.flickable: TextArea {
                    id: txtArea
                    text: "TextArea\n...\n...\n...\n...\n...\n...\n"
                    font.family: "Helvetica"
                    font.pointSize: 20
                    color: "blue"
                    wrapMode: TextArea.Wrap

                    Text {
                        id: text1
                        x: 483
                        y: 70
                        text: qsTr("Text")
                        font.pixelSize: 12
                    }
                }

                ScrollBar.vertical: ScrollBar { }
                //ScrollBar can thiệp sâu vào thanh scroll, scrollview chỉ là có thể xem đc cj bằng scroll
            }
        }
    }
}
//Về Flickable: đây là một tính năng có tác dụng rê item, dùng nó thì k cần dùng scrollbar cx đc, giống kiểu hình bàn tay ấy
//Ta hiểu scrollView và Flickable nó như là 1 cái màn hiển thị nội dung. Nó hiển thị nội dung trong 1 cái khung nhỏ do ta
//set kích thước tùy ý. Nếu như kích thước của content mà vượt quá khung thì ta có thể dùng scrollbar or flick để rê đến vị
//trí cần xem. Giới hạn của màn là vô hình ta k nhìn thấy nên mới khó hiểu. Tuy nhiên như ta đã biết nếu như màn hình đủ to
//thì ta vẫn sẽ nhìn thấy hết thôi. Chính vì v nên ng ta ms thường set width và height full kín cái phạm vi hiển thị của ta,
//còn contentWidth và contentHeight là phạm vi của item để nếu như kích thước item mà lớn hơn phạm vi khung của cái đó thì
//ta sẽ flick or scroll để nhìn hết cái vùng content ta set đó

//Chú ý là flick là mục đích để di đến vị trí mong muốn để hiển thị ra chứ kéo quá cái item chả có tác dụng gì, nó sẽ tự
//quay về vị trí gốc. Có thể cản với boundsBehavior:Flickable.stopAtBounds
//Ví dụ ta cho contentWidth và contentHeight trùng với width và height của Flickable thì k có hiệu ứng gì hết vì phạm vi
//khung hiển thị của Flickable là width và height luôn bao hết phạm vi cần hiển thị là contentWidth và contentHeight nên
//k cần flick gì cả. Tức là ta set width và height cho nó, r sau đó set contentWidth và contentHeight và từ đó trở đi, nếu
//như contentWidth và contentHeight vượt quá cái khung là width và height thì sẽ có thể flick. ScrollView cx tương tự, nó cx
//có contentHeight và contentWidth nhưng ta k set, mặc định nó theo kích thước của con.
//Tính chất ta đã biết đó chính là con đè lên cha. Nhưng không bị giới hạn trong phạm vi của cha. Tức là nếu con kích thước
//lớn hơn cha thì vẫn hiển thị tràn ra ngoài bth, nếu màn hình đủ rộng thì vẫn nhìn thấy thôi. Do đó tính chất clip:true sẽ
//khiến cho con bị cắt chỉ hiển thị bên trong phạm vi kích thước khung hiển thị. Đó là với Flickable còn ScrollView kích
//thước của item tự động bị giới hạn trong cái khung của scrollbar mà ta k cần phải clip:true->đương nhiên vì nếu scrollbar
//mà clipfalse thì tưởng tượng nó chả ra cái gì cả

//contentHeight và contentWidth là phạm vi của nội dung bên trong. Cứ như kiểu phạm vi bên trong của scrollView ấy, khi ta
//set thì nó là phạm vi mà có thể scroll tới hay ở đây là flick tới. Ví dụ item bên trong cao 5000 pixel mà ta set cho
//contentHeight là 1000 pixel thì ta chỉ có thể rê nó xuống để nhìn đc hết 1000 pixel thôi chứ k xem hết phần bên dưới được.

//nếu selectByMouse là true thì sẽ hiệu ứng flick sẽ k có tác dụng khi ấn vào văn bản mà nó sẽ thành chọn văn bản, là false
//thì vẫn hiện như bth. 2 tính năng trùng nhau nó ưu tiên lấy cái cụ thể của textArea hơn.
//Thật ra nếu selectByMouse cả 1 cụm dài xong lại Flickable thì k nên vì nếu ta gõ hết đủ 1 dòng và quá 1 trang thì tính
//năng Flickable sẽ kbh còn hiệu lực nx. Do đó chỉ nên dùng 1 trong 2 or dùng select thì nên prefer cái scrollView hơn.

//TextArea khi set kích thước fix thì giới hạn hiển thị của nó sẽ ở trong vùng kích thước đó, nếu vượt quá nó thì biến mất
//k xem đc or scroll đc với version 1.3
//TextArea khi không set kích thước thì nó sẽ tự mang theo kích thước của cha. Nếu k làm đc điều đó thì kích thước của nó
//mặc định động 0,0 và tự mở rộng khi ta gõ thì càng kéo dài.
//VD: khi ta set kích thước 100 width thì gõ vượt quá 100 sẽ biến mất. Khi dùng là con của ScrollView bên trên mà scrollview
//mang kích thước của parent là cả hcn, nên nó bao cả hcn, do đó ta ấn vào bất của vùng nào của text cũng đều focus vào dòng
//đó của TextArea. Khi dùng là con của Flickable ta k set width height nên nó mang kích thước hiển thị content của Flickable
//Nhưng kích thước đó lại tùy vào ban đầu nên k set đc và mang giá trị động. Nó sẽ là 0,0 r từ từ mở rộng ra khi gõ text
//Do đó ta click chuột vào các vị trí ở xa mà text chưa gõ tới theo cả chiều dọc và ngang thì TextArea đều k bị focus.
//=>đó là sự khác biệt về tính chất của Flickable và scroll, scroll thì mọi chỗ đều focus content, flick thì éo

//Đặc biệt nếu width height trùng contentWidth contentHeight thì sẽ k flick nhưng nếu width và height lớn hơn contentwidth,
//contentheight thì vẫn flick được nhưng chả để làm gì cả, chỉ là flick được cho nó đẹp thôi vì cái khung nó lớn hơn phạm
//vi có thể hiển thị và cần hiển thị thì luôn hiện đủ r.


//TH lý tưởng ví dụ ta cần xem file pdf thì phải vừa có thanh scrollbar, vừa có Flickable mà lại edit đc khi click vào pham
//vi cơ(Đã Flick thì k chọn cả cụm v)-> Tuy nhiên để làm đc điều này hiểu bc k đơn giản. Ta xét 2 cách sai để hiểu:

//C1: Dùng Flick bao ngoài scroll với scroll sẽ anchors.fill:parent thì nó sẽ k hiển thị gì cả. NN vì Flick kích thước là cả
//khung hcn. Xong ScrollView nó fill parent là cái flickable nhưng khổ là nó sẽ k mang kích thước của khung FLickable mà là
//mang kích thước của phạm vi hiển thị content mà thôi->Đây là cái trap dễ nhầm vì con mang kích thước khung của cha chỉ khi
//cha là 1 item bth,còn đây là 1 cái màn hiển thị thì nó chỉ đc mang kích thước của phạm vi hiển thị content của màn mà thôi
//Lúc này scrollView đc set kích thước của chính nó thành ra là 0,0 éo hiển thị gì cả. Ta vẫn cho nó hiển thị bằng cách cho
//ScrollView kích thước là của khung rectangle luôn. Khi đó cái textarea mang phạm vi toàn bộ cái khung hiển thị của scroll
//view và ta focus nó bằng cách click mọi vị trí của scrollView
//scrollView contentWidth và contentHeight là chính width và height của nó
//Khi đó, dùng được flickable khi text chưa quá 1 khung của scrollView, quá r thì chỉ dùng đc scrollView, k dùng đc flickable
//NN vì khi chưa quá khung của scrollView thì scrollbar chưa xuất hiện nên dùng được. Khi quá thì scrollbar xuất hiện. Nên
//nhớ rằng người ta luôn ưu tiên dùng scrollbar hơn là flick nên khi đó flick bị vô hiệu hóa ở phạm vi khung của scrollbar,
//nơi mà ưu tiên dùng scrollbar hơn, khi đó flick sẽ là 1 cái bao bên ngoài scrollbar nhưng có vẻ như không hữu dụng.
//Ở ví dụ trên ta đã cố làm nó hữu dụng: lúc chưa dùng được scrollbar nhưng kích thước của scrollbar đã vượt quá khung flick
//nên contentWidth và contentHeight có thể kéo đến được để xem. Khi đã vượt quá khung scrollView thì scrollbar xuất hiện và
//ưu tiên nên trong khung của scrollView SẼ K THỂ DÙNG ĐC FLICK. Thay vào đó ta dùng flick ở ngoài khung scrollview được.
//Ở TH này flick là cần thiết thì mới nhìn hết khung scrollbar đc
//kp scrollbar luôn ưu tiên hơn đâu mà là nó cụ thể bên trong nên được ưu tiên hơn bên ngoài thôi

//C2: Nếu dùng ScrollView là cha của Flickable thì khi click vào 1 điểm ở xa mà text chưa trỏ tới sẽ k focus vào văn bản vì
//text nó vẫn là con của Flickable như trên đã nói. Tính năng FLick sẽ bị vô hiệu vì xung đột với thanh scroll. Ở TH này nó
//bị bỏ đi luôn vì cả vùng không gian có scroll bar hết.

//Để dùng hoàn chỉnh ta dùng Attached Properties. Attached Properties là thuộc tính của 1 class có tác dụng gán 1 object này
//với 1 objec khác được định nghĩa sẵn theo 1 hướng. Bởi vì nó chỉ đính 1 object vào trong 1 object cụ thể. Để kết hơp
//scrollView với Flickable hoàn hảo thì ta dùng thuộc tính vertical của ScrollBar còn những thứ khác giữ nguyên. Như v cái
//ScrollView sẽ k còn ưu tiên hơn Flickable nx. Và ta có thể cải tiến dùng attached properties của textarea là flickable.
//Thuộc tính này sẽ gán textarea vào trong phạm vi cần hiển thị của cái Flickable mà thôi, ta gán chay cx đc.
//=>Khi muốn kết hợp cj vs cj nên kiểm tra attached properties. Chú ý scrollbar khác scrollview
