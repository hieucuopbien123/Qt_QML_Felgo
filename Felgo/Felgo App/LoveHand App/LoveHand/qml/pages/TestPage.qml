import QtQuick 2.0
import Felgo 3.0

Page {
    title: "Test Page"
    AppButton{
        anchors.centerIn: parent
        text: "Fetch"
        onClicked: {
            logic.querySearch("cây thông đất ham muốn")
        }
    }
    Connections{
        target: dataModel
        onFinishSearch:{
            console.log("Finish fetching")
            navigationStack.popAllExceptFirstAndPush(productListComponent)
        }
    }
    Component{
        id: productListComponent//id phải bắt đầu bằng chữ lower case
        TestListPage{}
    }
}
