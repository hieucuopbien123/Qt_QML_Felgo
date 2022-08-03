import QtQuick 2.0
import Felgo 3.0

//nếu có nhiều client thì tên file nên specific
Item {
    //xử lý icon quay quay ở page search. icon đó thg dùng khi lấy dữ liệu trên web
    readonly property bool loading: HttpNetworkActivityIndicator.enabled//(bôi đen)+ấn tab d dể nhảy sang chữ kế
    //HttpNetworkActivityIndicator lưu thông tin request có enabled tự động true false khi app gọi request cho internet
    //nó là thứ tồn tại trong mọi device android, iOS luôn có 1 cái indicator cực kỳ nhỏ báo hiệu ta dùng 1 network request
    //vào cái biến này truy cập vào cái indicator đó
    Component.onCompleted: {
        HttpNetworkActivityIndicator.activationDelay = 0
        //sau khi khởi tạo request thì cái indicator sẽ chờ 1 ktg thì cái indicator mới được enabled, độ trễ đó mặc định là 1s
        //nhưng nếu ta k muốn chờ mà khởi tạo phát có luôn nên set là 0-> khi gán cho cái icon kia r thì nó sẽ hiện luôn khi
        //search chứ k chờ 1s ms hiện nx
    }//Component đóng gói cái qml type lại. Nó đc define bởi cái file, đó là Client{} này đó
    //Nó có slot onDestruction và onCompleted thực hiện khi phát ra ra signal completed và destruction khi khởi tạo và bị xóa đi
    //Nó như kiểu component lifeCycle của js nhưng thô sơ hơn chỉ có 2 cái trên thôi
    Item {
        id: _//private member, chỉ dùng trong class Item bên ngoài
        readonly property string serverUrl: "https://felgo.com/mockapi-propertycross?country=uk"
        function buildUrl(paramMap){
            var url = serverUrl
            for(var param in paramMap){
                url += "&" + param + "=" + paramMap[param]
            }
            return url
        }
        //Nó khuyên rằng ta nên lưu lại cái param cuối cùng của url vì thg dùng vào vc j đó
        property var lastParamMap: ({})
        function sendRequest(paramMap,callback){//callback tự định nghĩa sẽ tự động bất đồng bộ
            var method="GET"
            var url = buildUrl(paramMap)
            console.debug(method + ": " + url)

            HttpRequest.get(url)//cần mỗi url là đc r
            .then(function(res){
                var content = res.text//1 cách lấy dữ liệu response từ http request
                try{
                    var obj = JSON.parse(content);
                }
                catch(ex){
                    console.error("Could not parse JSON: " + ex);
                }
                console.debug("Success parsing JSON")
                callback(obj);
            })
            .catch(function(err){
                console.debug("Fatal error in URL GET");
            })
        }
    }
    //Bên trên là các hàm private, bh ta sẽ định nghĩa ra các hàm public dùng được ở mọi nơi ta muốn
    function search(text, callback){
        _.sendRequest({
                        action: "search_listings",
                        page: 1,
                        place_name: text
                      },callback)
    }
    function searchByLocation(latitude, longtitude, callback){
        _.sendRequest({
                          action: "search_listings",
                          page: 1,
                          centre_point: latitude + "," + longtitude
                      },callback)
    }
    function repeatForPage(page, callback){//ta lại muốn truy cập vào page khác, vẫn địa chỉ đó
        var params = _.lastParamMap
        params.page = page
        _.sendRequest(params, callback)
    }
    //1 object gọi hàm search->Item được ra->phát signal completed và thực hiện->lấy hàm search và thực hiện->gọi sendRequest đó
    //lấy url và build lên hoàn chỉnh nối vào cái &action=search_listing&page=1&place_name=<nội dung thanh input>-> gọi hàm get cái
    //url nó, parse json trả về object bth và bắt lỗi nếu có, gọi callback cái object đó => gọi repeatForPage-> gán lastParam thêm
    //thuộc tính page bao nhiêu-> sendRequest. Chưa xử lý nhưng ý tưởng là ta sẽ cho lastParam sẽ lưu các params lấy lần cuối và
    //thêm page bằng bao nhiêu ở cuối sẽ đè lên cái page trước để lấy url
    //Để dùng search: khai báo callback có dữ liệu thì làm gì, ấn nút thì gọi hàm search truyền vào content người dùng nhập ở input
    //và hàm callback. Để dùng repeatForPage thì lấy số trang ng dùng muốn truyền vào kèm với call back là xong
}












