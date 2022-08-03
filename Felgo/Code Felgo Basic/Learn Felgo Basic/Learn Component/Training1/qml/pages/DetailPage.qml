import QtQuick 2.0
import Felgo 3.0

//test các hàm global
Page {
//    backgroundColor: Qt.lighter("lightsteelblue",1.2)
    //trong dải tint có các con số chỉ mức độ thì là đối số 2, 1 là màu chủ đạo

    //Theme là cái có trong Felgo dùng để styling app của ta, đặc biệt là nó khác nhau tương thích với
    //tùy phiên bản iOS, Android chứ k như 1 màu cố định
    backgroundColor: Theme.colors.selectedBackgroundColor

    clip: true
    opacity: 0.5
    title: "Title"
    useSafeArea: true
    Component.onCompleted: {
        console.log(Qt.size(10,10))
        console.log(Qt.rect(1,2,3,4))
        console.log(Qt.point(1,2))
        console.log(Qt.md5("Nguyen Thu Hieu"))//mã hóa
        console.log(Qt.tint("lightsteelblue", "#10FF0000")) //(<basecolor>,<tintcolor>)
    }
    AppButton{
        text: "Quit"
        anchors.centerIn: parent
        onClicked: Qt.quit()
    }
    Text{
        text:"Hello"
        //text mà muốn wrap phải set width cho nó
    }
    //1 page bình thường sẽ k có scrollbar nhé
}
