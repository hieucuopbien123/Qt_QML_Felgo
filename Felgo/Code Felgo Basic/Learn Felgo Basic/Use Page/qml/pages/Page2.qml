import QtQuick 2.0
import Felgo 3.0

Page {
    title: "Page2"
//    AppButton{
//        text: "Next"
//        onClicked: {
//            console.log(navigationStack.leftColumnIndex)
//            console.log("Depth: " + navigationStack.depth)
////            navigationStack.popAllExceptFirstAndPush(testComp2)
////            navigationStack.push(testComp2)
//            navigationStack.popAllExceptFirst()
//        }
//    }
    AppButton{
        text: "Next"
        anchors.centerIn: parent
        onClicked: {
            console.log(navigationStack.leftColumnIndex)
            console.log("Depth: " + navigationStack.depth)
            navigationStack.push(testComp1)
        }
    }
    Component{
        id: testComp1
        Page1{ }
    }
    Component{
        id: testComp2
        PageList1{ }
    }
}
