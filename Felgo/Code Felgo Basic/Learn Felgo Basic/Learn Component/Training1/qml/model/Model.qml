import QtQuick 2.0
import Felgo 3.0
import Qt.labs.settings 1.1

Item {
    property alias dispatcher: logicConnection.target
    signal finishFetching(string dataOfSignal)
    Client{
        id: client
    }
    Connections{
        id: logicConnection
        onTestGet: {
            client.testGET(_.responseCallback)
        }
    }
    Item{
        id: _
        readonly property var successCodes: ["100","101","110"]
        readonly property var ambiguousCodes: ["200","202"]
        property var count: 0
        //có các trang web beautify dữ liệu json để nhìn cho dễ đó
        function responseCallback(obj){
            var response = obj.length
//            nếu dữ liệu trả ra có kèm mã code thì nên check
            console.log("Before: " + count)
            count = response
            countChanged()
            console.log("After: " + count)
            console.log(settingModel.count)
            finishFetching("This is data of signal")
        }
    }
    Settings{//địt mẹ phải import chứ
        id: settingModel
        property var count: _.count//trong js là var, ngoài qml là type như C++
        Component.onCompleted: {
            _.count = count
        }
    }
}
