import QtQuick 2.0
import Felgo 3.0
import Qt.labs.settings 1.1

Item {
    RestAPI{
        id: api
    }
    signal finishBlogGetting(var model, string titleParam)//biến object hay array của js thì đặt type là var
    property alias dispatcher: logicConnection.target
    property var productList1: _.createProductList()
    readonly property alias searchedBlogs: _.searchedBlogs
    readonly property alias loading: api.loading
    readonly property alias favouriteList: _.favouriteList
    signal finishSearch()
    signal editFinish(int index)
    function isFavourite(titleParam){
        return (_.listTitle.indexOf(titleParam) >= 0);
    }

    Connections{
        id: logicConnection
        onQueryProduct: {
            console.log("Signal catched")
            api.queryProduct("product",_.callbackProduct)
        }
        onQuerySearch: {
            console.log("Searching")
            api.querySearch(searchString,_.callbackSearch)
        }
        onToggleFavourite: {
            var index = _.listTitle.indexOf(titleParam)
            if(index < 0){
                console.debug("FavouriteList added a new item")
                _.favouriteList.push({title: titleParam, content: contentParam});
            }else {
                console.debug("FavouriteList remove this item")
                _.favouriteList.splice(index, 1)//xóa phần tử khỏi mảng trong js
            }
            editFinish(index)
            _.favouriteListChanged(index)
        }
        onQueryBlog: {
            console.log("Signal catched")
            switch(code){
                case 182:
                    if(_.tamlinhs.length == 0)
                        api.queryBlog(code,_.callbackBlog)
                    else
                        finishBlogGetting(_.tamlinhs,"Tâm linh")
                    break;
                case 184:
                    if(_.thiens.length == 0)
                        api.queryBlog(code,_.callbackBlog)
                    else
                        finishBlogGetting(_.thiens,"Thiền - Yoga")
                    break;
                case 183:
                    if(_.hocs.length == 0)
                        api.queryBlog(code,_.callbackBlog)
                    else
                        finishBlogGetting(_.hocs,"Học tập")
                    break;
                case 179:
                    if(_.lamdeps.length == 0)
                        api.queryBlog(code,_.callbackBlog)
                    else
                        finishBlogGetting(_.lamdeps,"Làm đẹp")
                    break;
                case 180:
                    if(_.lamgiaus.length == 0)
                        api.queryBlog(code,_.callbackBlog)
                    else
                        finishBlogGetting(_.lamgiaus,"Làm giàu")
                    break;
                case 181:
                    if(_.amthucs.length == 0)
                        api.queryBlog(code,_.callbackBlog)
                    else
                        finishBlogGetting(_.amthucs,"Ẩm thực")
                    break;
                case 185:
                    if(_.giaitris.length == 0)
                        api.queryBlog(code,_.callbackBlog)
                    else
                        finishBlogGetting(_.giaitris,"Giải trí")
                    break;
                case 186:
                    if(_.socuus.length == 0)
                        api.queryBlog(code,_.callbackBlog)
                    else
                        finishBlogGetting(_.socuus,"Sơ cứu - Cấp cứus")
                    break;
                case 190:
                    if(_.ungthus.length == 0)
                        api.queryBlog(code,_.callbackBlog)
                    else
                        finishBlogGetting(_.ungthus,"Ung thư")
                    break;
                case 141:
                    if(_.phongtranhs.length == 0)
                        api.queryBlog(code,_.callbackBlog)
                    else
                        finishBlogGetting(_.phongtranhs,"Phòng tránh")
                    break;
                case 188:
                    if(_.nguoigias.length == 0)
                        api.queryBlog(code,_.callbackBlog)
                    else
                        finishBlogGetting(_.nguoigias,"Bệnh người già")
                    break;
                case 189:
                    if(_.phunus.length == 0)
                        api.queryBlog(code,_.callbackBlog)
                    else
                        finishBlogGetting(_.phunus,"Bệnh phụ nữ")
                    break;
                case 187:
                    if(_.treems.length == 0)
                        api.queryBlog(code,_.callbackBlog)
                    else
                        finishBlogGetting(_.treems,"Bệnh trẻ em")
                    break;
                case 191:
                    if(_.thuonggaps.length == 0)
                        api.queryBlog(code,_.callbackBlog)
                    else
                        finishBlogGetting(_.thuonggaps,"Bệnh thường gặp")
                    break;
                case 193:
                    if(_.thuocnams.length == 0)
                        api.queryBlog(code,_.callbackBlog)
                    else
                        finishBlogGetting(_.thuocnams,"Bài thuốc nam")
                    break;
            }

        }
    }
    Item{
        id: _
        property var products: []
        property var tamlinhs: []
        property var thiens: []
        property var hocs: []
        property var lamdeps: []
        property var lamgiaus: []
        property var amthucs: []
        property var giaitris: []
        property var socuus: []
        property var ungthus: []
        property var phongtranhs: []
        property var nguoigias: []
        property var phunus: []
        property var treems: []
        property var thuonggaps: []
        property var thuocnams: []
        property var searchedBlogs: []
        property var favouriteList: []
        property var listTitle: favouriteList.map(function(item) {return item.title})
        function callbackSearch(obj){
            searchedBlogs = []
            var titleRes;
            for(var i = 0; i < obj.length; i++){
                titleRes = fixTitle(obj[i].title.rendered);
                searchedBlogs = searchedBlogs.concat([{
                                                        title: titleRes,
                                                        content: obj[i].content.rendered
                                                     }])
            }
        }
        function fixTitle(titleParam){
            var from = titleParam.indexOf("&");
            var to = titleParam.indexOf(";")
            if(from < 0 || to < 0)
                return titleParam
            console.log("Before: " + titleParam)
            var abc = titleParam.slice(0,from) + titleParam.slice(to + 1)
            console.log("After: " + abc)
            return abc;
        }

        function callbackBlog(obj,code){
            console.log("callback called blog")
            var title;
            var i;
            var titleRes;
            switch(code){
                case 182:
                    title = "Tâm linh";
                    tamlinhs = [];
                    for(i = 0; i < obj.length; i++){
                        titleRes = fixTitle(obj[i].title.rendered);
                        tamlinhs = tamlinhs.concat([
                                                    {
                                                        title: titleRes,
                                                        content: obj[i].content.rendered
                                                    }
                                                ]);
                        console.log(obj[i].title.rendered);
                    }
                    finishBlogGetting(tamlinhs,title);
                    break;
                case 184:
                    thiens = []
                    title = "Thiền - Yoga";
                    for(i = 0; i < obj.length; i++){
                        titleRes = fixTitle(obj[i].title.rendered);
                        thiens = thiens.concat([
                                                    {
                                                        title: titleRes,
                                                        content: obj[i].content.rendered
                                                    }
                                                ]);
                        console.log(obj[i].title.rendered);
                    }
                    finishBlogGetting(thiens,title);
                    break;
                case 183:
                    title = "Học tập";
                    hocs = []
                    for(i = 0; i < obj.length; i++){
                        titleRes = fixTitle(obj[i].title.rendered);
                        hocs = hocs.concat([
                                                    {
                                                        title: titleRes,
                                                        content: obj[i].content.rendered
                                                    }
                                                ]);
                        console.log(obj[i].title.rendered);
                    }
                    finishBlogGetting(hocs,title);
                    break;
                case 179:
                    title = "Làm đẹp";
                    lamdeps = []
                    for(i = 0; i < obj.length; i++){
                        titleRes = fixTitle(obj[i].title.rendered);
                        lamdeps = lamdeps.concat([
                                                    {
                                                        title: titleRes,
                                                        content: obj[i].content.rendered
                                                    }
                                                ]);
                        console.log(obj[i].title.rendered);
                    }
                    finishBlogGetting(lamdeps,title);
                    break;
                case 180:
                    title = "Làm giàu";
                    lamgiaus = []
                    for(i = 0; i < obj.length; i++){
                        titleRes = fixTitle(obj[i].title.rendered);
                        lamgiaus = lamgiaus.concat([
                                                    {
                                                        title: titleRes,
                                                        content: obj[i].content.rendered
                                                    }
                                                ]);
                        console.log(obj[i].title.rendered);
                    }
                    finishBlogGetting(lamgiaus,title);
                    break;
                case 181:
                    title = "Ẩm thực";
                    amthucs = []
                    for(i = 0; i < obj.length; i++){
                        titleRes = fixTitle(obj[i].title.rendered);
                        amthucs = amthucs.concat([
                                                    {
                                                        title: titleRes,
                                                        content: obj[i].content.rendered
                                                    }
                                                ]);
                        console.log(obj[i].title.rendered);
                    }
                    finishBlogGetting(amthucs,title);
                    break;
                case 185:
                    giaitris = []
                    title = "Giải trí";
                    for(i = 0; i < obj.length; i++){
                        titleRes = fixTitle(obj[i].title.rendered);
                        giaitris = giaitris.concat([
                                                    {
                                                        title: titleRes,
                                                        content: obj[i].content.rendered
                                                    }
                                                ]);
                        console.log(obj[i].title.rendered);
                    }
                    finishBlogGetting(giaitris,title);
                    break;
                case 186:
                    socuus = []
                    title = "Sơ cứu - Cấp cứu";
                    for(i = 0; i < obj.length; i++){
                        titleRes = fixTitle(obj[i].title.rendered);
                        socuus = socuus.concat([
                                                    {
                                                        title: titleRes,
                                                        content: obj[i].content.rendered
                                                    }
                                                ]);
                        console.log(obj[i].title.rendered);
                    }
                    finishBlogGetting(socuus,title);
                    break;
                case 190:
                    title = "Ung thư";
                    ungthus = []
                    for(i = 0; i < obj.length; i++){
                        titleRes = fixTitle(obj[i].title.rendered);
                        ungthus = ungthus.concat([
                                                    {
                                                        title: titleRes,
                                                        content: obj[i].content.rendered
                                                    }
                                                ]);
                        console.log(obj[i].title.rendered);
                    }
                    finishBlogGetting(ungthus,title);
                    break;
                case 141:
                    title = "Phòng tránh";
                    phongtranhs = []
                    for(i = 0; i < obj.length; i++){
                        titleRes = fixTitle(obj[i].title.rendered);
                        phongtranhs = phongtranhs.concat([
                                                    {
                                                        title: titleRes,
                                                        content: obj[i].content.rendered
                                                    }
                                                ]);
                        console.log(obj[i].title.rendered);
                    }
                    finishBlogGetting(phongtranhs,title);
                    break;
                case 188:
                    title = "Bệnh người già";
                    nguoigias = []
                    for(i = 0; i < obj.length; i++){
                        titleRes = fixTitle(obj[i].title.rendered);
                        nguoigias = nguoigias.concat([
                                                    {
                                                        title: titleRes,
                                                        content: obj[i].content.rendered
                                                    }
                                                ]);
                        console.log(obj[i].title.rendered);
                    }
                    finishBlogGetting(nguoigias,title);
                    break;
                case 189:
                    title = "Bệnh phụ nữ";
                    phunus = []
                    for(i = 0; i < obj.length; i++){
                        titleRes = fixTitle(obj[i].title.rendered);
                        phunus = phunus.concat([
                                                    {
                                                        title: titleRes,
                                                        content: obj[i].content.rendered
                                                    }
                                                ]);
                        console.log(obj[i].title.rendered);
                    }
                    finishBlogGetting(phunus,title);
                    break;
                case 187:
                    title = "Bệnh trẻ em";
                    treems = []
                    for(i = 0; i < obj.length; i++){
                        titleRes = fixTitle(obj[i].title.rendered);
                        treems = treems.concat([
                                                    {
                                                        title: titleRes,
                                                        content: obj[i].content.rendered
                                                    }
                                                ]);
                        console.log(obj[i].title.rendered);
                    }
                    finishBlogGetting(treems,title);
                    break;
                case 191:
                    title = "Bệnh thường gặp";
                    thuonggaps = []
                    for(i = 0; i < obj.length; i++){
                        titleRes = fixTitle(obj[i].title.rendered);
                        thuonggaps = thuonggaps.concat([
                                                    {
                                                        title: titleRes,
                                                        content: obj[i].content.rendered
                                                    }
                                                ]);
                        console.log(obj[i].title.rendered);
                    }
                    finishBlogGetting(thuonggaps,title);
                    break;
                case 193:
                    title = "Bài thuốc nam";
                    thuocnams = []
                    for(i = 0; i < obj.length; i++){
                        titleRes = fixTitle(obj[i].title.rendered);
                        thuocnams = thuocnams.concat([
                                                    {
                                                        title: titleRes,
                                                        content: obj[i].content.rendered
                                                    }
                                                ]);
                        console.log(obj[i].title.rendered);
                    }
                    finishBlogGetting(thuocnams,title);
                    break;
                default:
                    break;
            }
        }
        function callbackProduct(obj){
            console.log("Callback called product")
            console.log(obj.length)
            products = []
//            for(var i = 0; i < obj.length; i++){
//                products.unshift(obj[i])
//                console.log(products[i].title.rendered)
//            }
            products = products.concat(obj)
//            productsChanged();
            console.log(products.length)
        }
        function createProductList(){
            console.log("create list")
            console.log(_.products.length)
            var check =  _.products.map(function(data){
                return {
                    text: data.title.rendered,
                    image: data.yoast_head_json.og_image[0].url,
                    //nếu ta gán image ở trong SimpleRow là sai vì là readonly và phải gán imageSource
                    //nhưng khi là 1 mảng các object ở model thì dùng đúng phải là image,text,detailText
                    model: data
                }
            })
            return check
        }
    }
    Settings{
        property var favouriteListingsValue:_.favouriteList
        Component.onCompleted: {
            _.favouriteList = favouriteListingsValue || []
        }
    }
}
//giải quyết vấn đề: productList1 được gán là createProductList, mà hàm này lại return ra 1 biến phụ thuộc vào
//_products => nó chỉ được gọi để gán khi _ products thay đổi. Như ta đã biết các property lúc đổi lúc k nên khi k
//đổi thì phải tự phát VD dùng concat thì đổi mà unshift từng phần tử thì k đổi
