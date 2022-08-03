import QtQuick 2.0
import Felgo 3.0

Page {
    useSafeArea: false
    title: "Page5"
    AppButton{
        signal newPageAppear
        id: button
        text: "Button"
        enabled: true
        flat: true
        onClicked: newPageAppear()
    }
    Connections{
        target: button
        onNewPageAppear: {
            navigationStack.popAllExceptFirstAndPush(componentForDetailPage6,{number: 10})
        }
    }
    Component{
        id: componentForDetailPage6
        DetailPage6{ }
    }
}
