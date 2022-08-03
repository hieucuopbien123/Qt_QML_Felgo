import QtQuick 2.0
import Felgo 3.0

Item {
    Item{
        id: _
        function buildUrl(params){
            return "https://catfact.ninja/fact"
        }
        function getData(params, callback){
            var url = buildUrl(params)
            HttpRequest.get(url)
            .then(function(res){
                var content = res.text
                try{
                    var obj = JSON.parse(content);
                }
                catch(ex){
                    console.error("Could not parse JSON: " + ex);
                }
                callback(obj);
            })
            .catch(function(err){
                console.debug("Fatal error in URL GET");
            })
        }
    }
    function testGET(callback){
        _.getData("Test URL",callback)
    }
}
