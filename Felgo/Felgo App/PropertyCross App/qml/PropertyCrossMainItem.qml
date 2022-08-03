import QtQuick 2.0
import Felgo 3.0
import "./pages"
import "model"

//ng ta thg tách file ra để tạo code logic ở 1 file, code hiển thị ở 1 file cho dễ pb
//file này trung gian sẽ thao tác với network và process logic, còn hiển thị sẽ giao cho file page nó ref tới
Item {
    anchors.fill: parent

    Logic {
        id: logic
    }

    DataModel{
        id: dataModel
        dispatcher: logic
    }

    PropertyCrossMainPage { }
}
