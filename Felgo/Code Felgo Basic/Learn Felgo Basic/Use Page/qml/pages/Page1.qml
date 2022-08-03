import QtQuick 2.0
import Felgo 3.0

Page {
    title: "Page 1"
//    AppButton{
//        text: "Next"
//        onClicked: {
//            console.log(navigationStack.leftColumnIndex)
//            console.log("Depth:" + navigationStack.depth)
//            navigationStack.popAllExceptFirstAndPush(testComp)
////            navigationStack.popAllExceptFirst()
//        }
//    }
//    Component{
//        id: testComp
//        Page2{ }
//    }

    AppButton{
        text: "Next"
        onClicked: {
            console.log("Depth:" + navigationStack.depth)
            navigationStack.push(testComp)
        }
    }
    Component{
        id: testComp
        Page2{ }
    }
}
//import QtQuick 2.0
//import Felgo 3.0

//Page {
//    title: "Page 1"
//    AppButton{
//        text: "Next"
//        onClicked: {
//            logic.openContent()
//        }
//    }
//    Connections{
//        target: model
//        onEnd:{
//            console.log("asdfasdf")
//            navigationStack.popAllExceptFirstAndPush(testComp)
//        }
//    }
//    Component{
//        id: testComp
//        PageList1{ }
//    }
//}
