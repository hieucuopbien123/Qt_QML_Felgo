import QtQuick 2.0
import Felgo 3.0
import Qt.labs.settings 1.1
//setting này tương tự QSetting trong Qt C++. Nên nhớ rằng cái này ta k dùng database vì dữ liệu nhỏ. Nếu dữ liệu lớn thì
//ta sẽ dùng database để lưu nó chứ k dùng setting qml

//có thể có nhiều model
Item {
    property alias dispatcher: logicConnection.target
    signal listingsReceived
    readonly property var listings: _.createListingsModel(_.listings)//data này chỉ cần hiển thị, k thay đổi
    //thuộc tính này như kiểu get biến private của class C++ => ta dùng 1 hàm private. truy cập private ở ngoài phải có id
    readonly property alias numTotalListings: _.numTotalListings
    readonly property int numListings: _.listings.length
    readonly property bool loading: client.loading
    //data model k có loading mà nó là của client
    readonly property var favouriteListings: _.createListingsModel(_.favouriteListingValues, true)
    Client{
        id: client
    }
    //connection sẽ làm nv xử lý signal
    Connections{
        id: logicConnection
        onSearchListings: {
            //dùng các biến truyền vào trong signal và trong phạm vi component này
            client.search(searchText, _.responseCallback)
        }
        onLoadNextPage: {
            client.repeatForPage(_.currentPage + 1, _.responseCallback)
        }
        //Trong demo ta có mỗi lần nó load 20 phần tử trong tổng số vài ngàn phần tử: thật ra ta k hề set cho nó chỉ load
        //20 item 1 lần mà là do kết quả trong 1 trang chỉ chứa chỉ có 20 item và JSON trả ra có thuộc tính lưu tổng
        //phần tử ta lấy đc chứ kp tìm ra mấy nghìn phần tử và mới chỉ load đến 20 phần tử.
        //Tức là k thể nào có chuyện nó load 20 phần tử r dừng lại và load tiếp như ta nghĩ, để đạt được điều đó thì cái
        //server gửi dữ liệu JSON phải chia theo trang, mỗi trang có 20 phần tử. Xong ta fetch API 1 trang, bắt signal khi
        //kéo cái thanh xuống cuối thì fetch trang tiếp theo. Khi đó cái listings của ta sẽ concat thêm dữ liệu ở trang 2
        //và cái listPage nó bind property biến listing sẽ tự động cập nhập màn hình chứ k cần phải phát signal cho nó bắt
        //để cập nhập nx.
        //Còn 1 lỗi nx là nếu dữ liệu trong 1 trang chưa đi quá kích thước màn hình thì cái signal onRefresh nó éo chạy, VD
        //trong chính cái app này fetch 5 dữ liệu k đủ 1 trang nó éo phát signal để load thêm trang 2(content y hệt trang 1)
        //mặc dù ta làm cho cái item load nó vẫn hiện nhưng sẽ k phát signal->chưa cần fix
        //Trong thực tế ít có khi nào nó cho thanh url kiểu 1 trang thì như v nhưng tư duy thì k đổi, vd ta cần fetch về
        //1000 item thì rõ ràng chả server nào 1 phát chứa cả ngàn cả mà nó sẽ chia theo 1 cái gì đó, có thể kp là trang
        //thì ta cx làm tương tự tức là phải tìm đc các trang url để fetch dữ liệu tiếp theo thì url đổi như thế nào để
        //fetch tiếp và tự cập nhập
        onToggleFavourite: {
            var listingDataStr = JSON.stringify(listingData)
            var index = _.favouriteListingValues.indexOf(listingDataStr)

            if(index < 0){
                console.debug("FavouriteList added a new item")
                _.favouriteListingValues.push(listingDataStr);
            }else {
                console.debug("FavouriteList remove this item")
                _.favouriteListingValues.splice(index, 1)//xóa phần tử khỏi mảng trong js
            }
            _.favouriteListingValuesChanged()//bind cái này thì phải phát ra
        }
    }
    //thích cái gì tái sử dụng ở trong các hàm của item thì tạo ra private riêng như này
    Item {//thuộc tính private k có từ khóa private mà lại nhét trong 1 item bên trong
        id:_
        //hàm callback sẽ cập nhập cái ui page, ta cần định nghĩa ra các biến sẽ sử dụng bên trong
        readonly property var successCodes: ["100","101","110"]//code return from server
        readonly property var ambiguousCodes: ["200","202"]
        property var locations: []
        property var listings: []
        property var favouriteListingValues: []
        property int numTotalListings
        property int  currentPage: 1
        onFavouriteListingValuesChanged: {
            console.log("VALUE CHANGED")
        }

        function responseCallback(obj){
            var response = obj.response
            var code = response.application_response_code
            console.debug("Server returned app code: " + code);
            //nếu có dữ liệu thành công thì lưu các thông tin cần dùng lại vào các biến khởi tạo bên trên
            //đó là các cái item trong list và dùng các thông tin đó để update cái page
            if(successCodes.indexOf(code) >= 0){
                //found location
                currentPage = parseInt(response.page)//lấy data bth từ API, lấy page
                listings = listings.concat(response.listings)//lấy list
                numTotalListings = response.total_results || 0//lấy tổng số các thành phần trong list
                listingsReceived();//Cơ chế cập nhập: lại signal cho cái page subcribe để cập nhập thôi
            }
            //ta dùng hàm này trong signal, slot, tức là mỗi lần ấn nút search là sẽ gọi hàm này, nhưng ta nên nhớ data model
            //xử lý các page là 1 biến khởi tạo 1 lần duy nhất, bên trong nó có 1 biến Item và nó k đổi, mà mỗi lần gọi ta
            //lại concat vào listing thì sẽ làm cho lần sau bị cộng dồn vào lần trc.Có thể fix bằng cách xóa nó đi trc khi dùng
            else if (ambiguousCodes.indexOf(code) >= 0){
                locations = response.locations//nếu trả ra
            } else if (code === "210"){//TH đặc biệt code này trả ra no result tìm đc
                locations = []
            } else {
                locations = []
            }
            //ta cứ xử lý tùy theo mã code trả ra, cái mã code trả ra là do server xử lý gửi về cho chúng ta
            //các mã code bên trên là các mã code phổ biến của http server mà ta cần phải xử lý
            //khi gặp code mã lỗi thì ta sẽ nhận đc location là cái ta search-> ta lấy location còn page và listings
            //ta để trống như default về sau sẽ k hiện gì cả
        }
        function createListingsModel(source, parseValues){
            //biến parseValues để tái sử dụng hàm này với favourite và dữ liệu lấy về mà thôi. Nếu có nhiều hơn thế thì
            //tạo nó thành 1 ENUM luôn cx đc
            console.log("Number of element in list: ", source.length);
            return source.map(function(data) {
                if(parseValues){//biến parseValues boolean bảo rằng có cần phải parse cái data truyền vào k. Chưa dùng
                    data = JSON.parse(data)
                }
                return {
                    text: data.price_formatted,
                    detailText: data.title,
                    image: data.thumb_url,
                    model: data//lấy từng thứ đồng thời lấy thêm tất cả data để còn dùng cả data cho các page con bên trong
                    //1 object có các trường như field của model
                }
            })
        }
    }
    //Để xử lý favourite thì cái model sẽ có biến private là 1 list các favourite(cái model nó như 1 cái store luôn v, các
    //biến của nó sẽ lưu các giá trị). Giả sử có cái list đó thì đơn giản kiểm tra list đó có chứa item này k là biết
    //isFavourite true hay false.
    //Cơ chế tự nghĩ: ấn thêm vào favourite là ở trong detail page, ta gọi đến 1 hàm thêm vào favouriteList của dataModel
    //hoàn toàn bth vì các page đều có thể dùng đc model. Xong mở favourite list sẽ hiện ra 1 page mới hiển thị SimpleRow các
    //favourite, nhưng để nó update tự động tức khi 1 phần tử của list biến mất thì cái favourite hiện ra cx mất item đó thì
    //ta sẽ dùng model gán source bind trực tiếp vào thuộc tính favouriteList của model, tức là chuyển thuộc tính đó từ private
    //sang public=>đó là cơ chế tự nghĩ
    function isFavourite(listingData){
        return _.favouriteListingValues.indexOf(JSON.stringify(listingData)) >= 0
    }

    Settings{
        property string favouriteListingsValue: JSON.stringify(_.favouriteListingValues)
        Component.onCompleted: {//onCompleted và onDestruction là 2 slot của Component, signal của nó gọi là
            //Attached signal đính kèm trong mọi class khác phát ra khi class đó đc khởi tạo or xóa
            _.favouriteListingValues = favouriteListingsValue && JSON.parse(favouriteListingsValue) || 0
        }//k cần onDestruction nx
    }
}
















