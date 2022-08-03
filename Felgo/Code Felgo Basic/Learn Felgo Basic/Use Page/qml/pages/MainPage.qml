import QtQuick 2.0
import Felgo 3.0

Page {
    title: "Main Page"
    NavigationStack {//1 page có stack chứa nhiều page
        id: navStack
        leftColumnIndex: 1
        splitView: tablet&&landscape //dùng split view(cái open document của qt,ấn vào gì thì chuyển view sang file khác)
        //tức set chỉ dùng splitView trên thiết bị tablet ở chế độ landscpae
        Page1 {}
    }
}
