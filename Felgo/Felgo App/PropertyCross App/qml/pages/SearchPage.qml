import QtQuick 2.0
import Felgo 3.0

Page {
    id: searchPage
    title: qsTr("Property Cross")

    //page để search sẽ có 1 thanh bar
    rightBarItem: NavigationBarRow {//1 cái thanh bar kích thước fix theo Navigation bar->chỉnh sửa thanh navbar bên phải
        ActivityIndicatorBarItem {//là 1 cái item biểu tượng tròn quay quay khi loading ấy
            visible: dataModel.loading
        }
        IconButtonBarItem {//cái nút bth nhưng đc dùng trong bar(riêng cho bar kiểu cho vừa kích thước phù hợp với bar ấy)
            //kế thừa từ qml Button bth
            icon: IconType.heart
            title: qsTr("Favourites")
            //trên iOS nó k responsive biến đổi thành menu icon khi màn hình nhỏ nhưng android thì có
            onClicked: showListing(true)
        }
    }
    //Nếu 1 App or 1 Page chỉ là 1 page cứng thì ta k nói làm gì, chỉ cần khai báo các component bên trong và phạm vi của app
    //hay page đó chính là toàn bộ phạm vi có thể hiển thị của nó, lúc chưa có gì thì sẽ full màn hình. Nhưng nếu 1 app muốn
    //có nhiều Page thì lại là vấn đề khác. Khi đó ta phải dùng NavigationStack, mặc định nó sẽ sinh ra 1 cái navigation bar
    //ở trên đầu, ta có thể chỉnh sửa nó, đồng thời cái navigation stack đó sẽ lưu 1 tập hợp các pages và chỉ hiển thị page ở
    //trên cùng của stack xuống bên dưới, tức phạm vi hiển thị của page chỉ là phần bên dưới của navigation bar. VD nếu cái
    //page trong navStack lại có 1 navStack thì sẽ hiện 2 thành nav bar theo thứ tự và page trong stack con sẽ có phạm vi
    //hiển thị chỉ bên dưới nav bar con. Tức là lúc này, biến navigationStack sẽ lưu 1 stack các page, ta có thể push thêm
    //1 page vào bằng hàm push nó sẽ push lên trên cùng của stack và hiển thị page mới. Khi push vào thì cái page mới thêm
    //sẽ thế vào đúng vị trí của cái page ban đầu. Và lúc này đương nhiên ta hiểu bản chất là cái thanh navbar khi hiển thị
    //1 page trong stack sẽ trống và tùy ý cho page đó chỉnh sửa thông qua title, rightBarItem,.., cái thanh đó kp của page
    //đó mà là của cái Page/App lớn ban đầu có navbar và các page chỉ đơn giản là chỉnh sửa nó hiển thị gì mà thôi.
    //navigation stack lưu các page trong 1 stack, ta có thể nhìn thấy chúng bằng cách dùng splitView thì nó sẽ hiển thị
    //ở left column, còn right column là thứ hiển thị nội dung. VD trong Qt thì left column là project, right là màn hình này
    //Các thứ ta thêm vào page hay app sau navigation stack sẽ đè lên nav stack và parent của nó là toàn bộ phạm vi hiển
    //thị của page/app, nhưng khi đã dùng navigationStack thì chỉ nên hiển thị bằng nó thôi, chả ai dùng component khác đè lên
    //transition mặc định khi hiện page mới theo tùy hệ điều hành tự có
    Column {
        id: contentCol
        anchors.left: parent.left
        anchors.top: parent.top
        anchors.right: parent.right
        anchors.margins: contentPadding//lấy thuộc tính từ file cha chứa nó
        spacing: contentPadding

        AppText {
            width: parent.width
            wrapMode: Text.WrapAtWordBoundaryOrAnywhere
            font.pixelSize: sp(12)//sp là screen point kiểu dp ấy
            //sp chỉ dùng cho font.pixel size còn dp thì dùng kiểu width height tương thích kích thước physical
            text: qsTr("Use the form below to search for houses to buy. You can seaech by place name, postcode or click 'My location'.")
        }

        AppText {
            width: parent.width
            font.pixelSize: sp(12)
            color: Theme.secondaryTextColor
            font.italic: true
            text: qsTr("You can quickly find something by typing 'London'...")
            wrapMode: Text.WrapAtWordBoundaryOrAnywhere
        }

        AppTextField {
            id: searchInput
            width: parent.width
            showClearButton: true//tính năng
            placeholderText: qsTr("Search...");
            inputMethodHints: Qt.ImhNoPredictiveText//xác định loại keyboard hiện ra

            onTextChanged: showRecentSearches()
            onEditingFinished: if(navigationStack.currentPage === searchPage)//code js
                                   search();
            //navigationStack sẽ truy cập vào NavigationStack của 1 item cha gần nhất. Cung sẵn k cân dùng id luôn. Mỗi Page
            //chỉ có duy nhất 1 nav stack. Nó cứ đi dần lên đến khi nào gặp cha có navigationStack thì dừng lại
            //VD ở TH này nó lấy navigation stack của cái page chứa cái search Page ở file PropertyCrossMainPage
        }
        Row {
            spacing: contentPadding
            AppButton{//Felgo làm lại hết
                text: qsTr("Go");
                onClicked: search()
            }
            AppButton{
                id: locationButton
                text: qsTr("Get my location")
                enabled: true
                onClicked: {//này là anonymous function
                    searchInput.text = ""
                    searchInput.placeholderText = qsTr("Looking for location...")
                    locationButton.enabled = false
                }
            }
        }
    }
    //viết function ở cấp 1 của Page thì mọi thứ trong page sẽ truy cập đc vào fucntion này
    function showRecentSearches(){
        console.log(searchInput.text);//giống log
    }
    /*k nên dùng hàm search viết httprequest ở đây vì k đúng structure và nếu k tốt nếu ta dùng nó ở nơi khác.
    Hàm search này ta nên put nó vào 1 client chứ k nên mỗi page tạo ra 1 http request client. Ta sẽ tạo ra 1
    client chuyên xử lý httpRequest
    function search(){
        HttpRequest.get("http://jsonplaceholder.typicode.com/posts")
        .then(function(res) {
            var content = res.text
            try{
                console.debug(content)
                var obj = JSON.parse(content);
            }
            catch(ex){
                console.error("Could not parse server response as JSON");
                return
            }
            console.debug("Success parsing JSON data");
        })
        .catch(function(err){
            console.debug("Failed: " + err);
        })
    }*/
    //Mục đích: ta muốn thao tác với app bth, khi thực hiện 1 công việc nặng nhọc-> nó sẽ làm bất đồng bộ, trong quá
    //trình đó, công việc đó bị block k thể thực hiện tiếp cho đến khi có kết quả nhưng các chức năng khác vẫn phải
    //hđ bth. Nếu thực hiện chức năng khác mà lại nặng nhọc thì nó sẽ thực hiện đồng thời với chức năng trc bất đồng
    //bộ
    //Thực tế qml có vòng sự kiện như js nên chuyện đó khỏi lo, khi ta thực hiện search nó lấy API, lấy xong sẽ thực
    //hiện then, trong lúc lấy thì ta vẫn dùng các thứ khác bth. Tự thân nó là như v rồi ta k cần lo về việc nó có
    //block hay k, chỉ cần quan tâm đến việc xử lý mà thôi
    function search(){
        logic.searchListings(searchInput.text,true)
    }
    function showListing(favourites){
        console.debug("Run here");
        if(navigationStack.depth === 1) {//số item hiện tại đã đc pushed vào trong stack. Nếu stack có 1 item
            //thì mới thực hiện-> đang fetch mà mở favourite thì sẽ k hiện, thích thế nào cx đc
            navigationStack.popAllExceptFirstAndPush(listPageComponent, {favourites: favourites})
            //xóa các page trừ page đầu tiên và push vào Stack 1 page mới. Page đầu tiên ở đây
            //là page ở leftColumnIndex có index=0; nó gọi ngầm 2 function là popAllExceptFirst và push, hiển nhiên là
            //k pop page đầu tiên thì mới còn cái mà hiển thị chứ. 1 là cái page ta push vào, 2 là option
            //hàm push(<source>,<option>); source là QMLfile, Component or Page(kiểu gì cx phải có Page k thì
            //thì k đúng kiểu). options là object trong JS trở thành property của cái source đó.
            //Các page add vào có thể, dùng các thuộc tính tự tạo trong nó, dùng các thuộc tính của ancestor qua id,
            //dùng các biến global để truy cập ví dụ navigationStack.
            //hàm push hiện page mới sẽ tự động có 1 cái button quay trở lại->button này sẽ giúp quay trở lại
            //page trước đó. Khi ấn quay lại, nó xóa cái page trên cùng stack luôn
            //Ta phải hiểu là hàm popAllExceptFirstAndPush xóa toàn bộ page trừ cái đầu nhưng các page nó xóa là kiểu khác
            //chứ kp là xóa các page trong navstack hiện tại như ta hiểu nên khi làm v hai lần thì hàm push sinh ra button
            //quay trở lại, ta phải click 2 lần button đó mới quay về ban đầu chứ kp nó xóa hết ấn 1 phát là quay về đầu
        }
    }
    Component {//thứ ta pop vào sẽ là 1 page, page này k đơn giản nên tạo 1 file mới
        id: listPageComponent
        ListingListPage {}
    }

    Connections{//chỉ chỉnh sửa vc hiển thị của cái file này bằng Component
        target: dataModel//làm nhanh k cần phải dispatcher lằng nhằng nx, chỉ cần nó cùng cấp với parent or
        //sibling thì truy cập đc id trực tiếp
        onListingsReceived: {
            console.debug("test");
            showListing(false);
        }
        onLocationReceived: if(searchInput.placeholderText === "Looking for location...")
                                searchInput.placeholderText = "Search";
    }
    Rectangle {
        color: "red"
        width: 50
        height: 50
        anchors.left: parent.left
        anchors.top: parent.top
    }
}















