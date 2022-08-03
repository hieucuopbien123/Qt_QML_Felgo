import QtQuick 2.0
import Felgo 3.0

Page {
    useSafeArea: true
    title: "Page 8"
    //dùng Flickable dễ vl chỉ cần set kích thước của nó và kích thước muôn nó hiển thị để nhìn tới là đc
    Flickable{
        id: flickableid
        anchors.fill: parent//xong kích thước của nó
        contentHeight: contentCol.height
        Column {
            id: contentCol
            width: parent.width
            Repeater {
                model: ["apples", "oranges", "pears"]
                Text { text: "Data: " + modelData }
            }
            Repeater {
                model: 10
                Text { text: "I'm item " + index }
            }
            Row {
                Rectangle { width: 10; height: 20; color: "red" }
                Repeater {
                    model: 10
                    Rectangle { width: 20; height: 20; radius: 10; color: "green" }
                }
                Rectangle { width: 10; height: 20; color: "blue" }
            }
            Repeater{
                model: [{name: "Hieu", age: 18}, {name: "Trang", age: 19}]
                delegate: Text{//các component bên trong mặc định sẽ nằm trong 1 cái delegate,tức code này có sẵn r
                    text: modelData.name + " - " + modelData.age
                }
            }
            Repeater{
                model: ListModel {
                        id: fruitModel
                        ListElement {
                            name: "Apple"
                            cost: 2.45
                        }
                        ListElement {
                            name: "Orange"
                            cost: 3.25
                        }
                        ListElement {
                            name: "Banana"
                            cost: 1.95
                        }
                    }
                delegate: SimpleRow{
                    width: parent.width
                    text: "Fruit: " + item.name + " - Cost: " + item.cost
                    item: fruitModel.get(index)
                    onSelected: {
                        fruitModel.append({"cost": 5.95, "name":"Pizza"})
                        //các model có nhiều hàm
    //                    clear() xóa hết
    //                    object get(int index)//lấy object ở vị trí nào
    //                    insert(int index, jsobject dict)//chèn object nào vào vị trí index nào
    //                    move(int from, int to, int n)//chuyển từ n item từ vị trí index from tới to
    //                    remove(int index, int count)//xóa count item từ vị trí index
    //                    set(int index, jsobject dict)//set object ở vị trí index nào là dict
                    }
                }
            }
        }
    //Repeater sẽ lặp lại cái component chứa trong nó theo model. model của nó là number chỉ số lượng component lặp
    //lại (sẽ dùng đc index) or 1 list string (sẽ dùng được modelData chỉ từng ptu mảng string) or 1 component
    //model của QML, cx có thể dùng 1 list object=> nch là số, list bất kỳ, model.
        ScrollIndicator {//scrollindicator là non interactive, k thể kéo thanh scroll đc
            flickable: flickableid
        }
        //thanh scroll này k chạy theo vị trí của ta, trong felgo thì kệ mẹ nó đi vì là mobile app
    }
}
