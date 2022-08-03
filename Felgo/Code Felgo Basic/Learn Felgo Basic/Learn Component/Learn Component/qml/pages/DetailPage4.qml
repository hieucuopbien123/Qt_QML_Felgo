import QtQuick 2.0
import Felgo 3.0
import QtQuick.Controls 1.4

Page {
    signal logout()
    AppButton{
        anchors.centerIn: parent
        text: "LogOut"
        onClicked: {
            logout()
        }
    }
}
