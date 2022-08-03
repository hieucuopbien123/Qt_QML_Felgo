import QtQuick 2.0
import Felgo 3.0

//xử lý hiển thị list và hiển thị favourites(khi biến favourites true)
//Ta có thể dùng 1 page hiển thị 2 cái kiểu này rất hay chỉ bằng vc thêm 1 biến boolean. Ta nhận thấy cái page favourite và
//page hiển thị content sau khi search nó giống hệt nhau chỉ là dữ liệu nó khác nhau=> ta có thể tái sử dụng chỉ bằng 1 page
//bằng cách cho nó hiển thị bth nhưng chỉ khác nhau về dữ liệu truyền vào đc quyết định bởi biến boolean mà thôi.
//Nếu k làm v thì vẫn có thể occho làm bth bằng cách ấn nút favourite thì lại popAllExceptFirstAndPush 1 component mới trỏ
//trỏ đến cái page mới và page đó viết y như này
ListPage {
    Component.onCompleted: {
        console.log("Load List Page Finish")
    }

    //ta có thể tạo kiểu 1 list xong add page vào bên trong thì nó kiểu như là menu ấy, nhưng ở đây ta sẽ tạo
    //hẳn 1 page chứa list các page khác chứ k dùng kiểu menu
    id: listPageWrapper
    property var scrollPos: null //lưu vị trí ta scroll trên page
    property bool favourites//mặc định bool là biến false nếu k set

    rightBarItem: ActivityIndicatorBarItem {
        //trên cái page mới này ta cx muốn có 1 cái spining báo hiệu đang lấy tiếp dữ liệu từ internet khi
        //scroll xuống tiếp sẽ lấy dần dần
        visible: dataModel.loading
        //loading là của client nhưng nằm trong dataModel thì cx là của dataModel
    }
    //model dùng cho dữ liệu list. Felgo cung JsonListModel dùng làm model cho JSON data source
    model: JsonListModel {
        id: listModel
        source: favourites ? dataModel.favouriteListings : dataModel.listings
        //hai biến này ta chưa có trong dataModel nên phải định nghĩa tạo ra. Mà dataModel có JSON nhận từ API. Còn
        //cái model này lại expect dữ liệu theo các trường fields bên dưới-> ta phải biến cái dữ liệu JSON ở dataModel
        //thành cái ta muốn nhận

        //source JSON của ta là cái gì
        fields: ["text","detailText","image","model"]//định nghĩa các trường
        //các trường này kp tự bịa ra, tên các trường là các thuộc tính của SimpleRow ta sử dụng
    }
    title: favourites ? qsTr("Favourites") : qsTr("%1 of %2 matches").arg(dataModel.numListings).arg(dataModel.numTotalListings)
    //numListings chưa tồn tại còn numTotal là private, ta xử lý sau, giả sử nó có
    emptyText.text: favourites ? qsTr("No favourites chosen") : qsTr("No listings available")
    //emptyText thuộc kiểu AppText và visible khi list k có phần tử nào sẽ tự hiện thay thế

    //Tới đây là cái model này có model dữ liệu, thanh navbar text hiện ra khi empty, còn thiếu các hiện thị như thế nào
    //delegate là 1 alias cung template để hiện thị mỗi item trong khởi tạo bởi view. Ví dụ ta muốn hiển thị theo kiểu row
    //như nào. Nó có index là biến lưu index của mỗi dữ liệu, cần dùng <model>.get(index) để lấy dữ liệu đó ra
    //tức là cái page là 1 view nhưng delegate chỉ là template mà cái view sẽ sử dụng để hiển thị model
    delegate: SimpleRow {//mỗi row của view sẽ hiển thị như này. SimpleRow là row mặc định
        item: listModel.get(index)
        //hiển thị item này ở row này, index đã giải thích bên trên, ta đang thao tác với 1 row hiển thị 1 item này
        //nó sẽ truyền vào các trường ở model
        //item của row là item lấy từ model có các trường như Row, khi đó k cần phải set-> detailText: ... nx
        //nó sẽ tự động hiển thị text là tiêu đề in đậm, ảnh bên trái, detailText chữ nhỏ...
        autoSizeImage: true//kích thước image sẽ đc auto fit
        imageMaxSize: dp(40)//kích thước auto nhưng cx k quá 40 đc
        image.fillMode: Image.PreserveAspectCrop//fill image như thế nào

        //nếu như cái row này đc chọn thì hiển thị detail bên trong lại là 1 page mới, như ta đã biết là hiển thị 1 Page
        //là xóa tất cả các page trừ page đầu tiên và push cái gì vào stack của page đầu tiên. Lại định nghĩa 1 page detail nx
        onSelected: {
            navigationStack.popAllExceptFirstAndPush(detailPageComponent, {model:item.model})
            //chỗ này có 2 page, push vào nx thành 3 page
        }
        //lúc này item của model nó là 1 object có các thuộc tính là trong field, truy cập vào bằng dấu chấm
        //ta phải truyền vào con or cách khác là làm cho model là 1 thuộc tính cua Page cha này thì các con truy cập bth
    }

    //Row là thứ rất ngốn bộ nhớ, đặc biệt là infinite scrolling row, ng ta có biện pháp recycling row để tránh tốn bộ
    //nhớ trong các app mobile->chưa học

    //khi đến cuối của list-> nếu hiển thị dữ liệu fetch đc(kp favourite) và số lượng dữ liệu chưa hết thì hiển thị Icon
    //còn kéo xuống tiếp-> nếu đến cuối
    listView.footer: VisibilityRefreshHandler{
        visible: !favourites && dataModel.numListings >= dataModel.numTotalListings
        //onRefresh phát khi kéo xuống cuối or kéo quá đầu
        onRefresh: {
            console.log("Phat loadNextPage")
            scrollPos = listView.getScrollPosition()//gán vị trí scrollPos hiện tại
            logic.loadNextPage()//phát signal load sang page tiếp theo
        }
    }
    Component{
        id: detailPageComponent
        ListingDetailPage {}
    }
}
