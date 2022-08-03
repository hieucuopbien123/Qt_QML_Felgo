import QtQuick 2.0
import Felgo 3.0

Item {
    readonly property bool loading: HttpNetworkActivityIndicator.enabled
    Component.onCompleted: {
        HttpNetworkActivityIndicator.activationDelay = 0
    }

    QtObject{
        id: _
        property string serverUrl: "https://lovehands.vn/wp-json/wp/v2/"
        function solveUrlProduct(paramUrl){
            return serverUrl + paramUrl
        }
        function solveUrlBlog(paramUrl){
            return serverUrl + "posts?categories=" + paramUrl + "&per_page=99";
        }
        function solveUrlBlogSearch(paramUrl){
            return serverUrl + "posts?search=" + paramUrl + "&per_page=99";
        }

        function getData(paramsUrl,callback,code = 0){
            HttpRequest.get(paramsUrl)
            .then(function(res) {
                console.log("Finish API")
                callback(res.body,code)
            })
            .catch(function(err) { console.log(err) });
            //nếu lấy res.text thì sẽ ra json của res, ta lại parse ra object or lấy res.body sẽ ra js object luôn
            //còn res là biến ResponseType. 2 cách lấy đó thì rõ ràng lấy body luôn tốt hơn
        }
    }
    function queryProduct(param,callback){
        _.getData(_.solveUrlProduct(param),callback);
    }
    function queryBlog(code,callback){
        _.getData(_.solveUrlBlog(code),callback,code)
    }
    function querySearch(search,callback){
        _.getData(_.solveUrlBlogSearch(search),callback)
    }
}
