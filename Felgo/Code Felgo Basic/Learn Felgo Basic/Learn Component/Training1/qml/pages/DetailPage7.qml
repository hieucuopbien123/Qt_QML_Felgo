import QtQuick 2.0
import Felgo 3.0

Page {
    useSafeArea: true
    title: "Page 7"
    GameButton{
        text: "Dialog"
        onClicked: {
            nativeUtils.displayMessageBox("Test Dialog","Description",2)
        }
    }
    AppImage {
        anchors.centerIn: parent
        source: "https://www.imgacademy.com/themes/custom/imgacademy/images/helpbox-contact.jpg"
        fillMode: Image.PreserveAspectFit
        width: 200
    }
}
