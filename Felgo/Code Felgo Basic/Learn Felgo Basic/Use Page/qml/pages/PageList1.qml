import QtQuick 2.0
import Felgo 3.0

ListPage {

    // TODO add your model
    title: "ádfasf"
    model: [{ type: "Fruits", text: "Banana" },
        { type: "Fruits", text: "Apple" },
        { type: "Vegetables", text: "Potato" }]

    section.property: "type"
    delegate: SimpleRow{
        onSelected: {
            navigationStack.popAllExceptFirstAndPush(testComp3)
        }
    }
    AppButton{
        text: "Next"
        onClicked: {
            console.log(navigationStack.leftColumnIndex)
            console.log("Depth: " + navigationStack.depth)
//            navigationStack.popAllExceptFirstAndPush(testComp3)
            navigationStack.popAllExceptFirst()
        }
    }
    Component{
        id: testComp3
        Page3{}
    }

}
