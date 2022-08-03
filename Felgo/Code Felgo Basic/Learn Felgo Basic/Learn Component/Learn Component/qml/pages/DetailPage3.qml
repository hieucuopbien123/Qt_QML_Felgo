import QtQuick 2.0
import Felgo 3.0

//khi ta sắp xếp vị trí của các component ta phải có tư duy là các component được render độc lập với nhau về vị trí
//Chúng sẽ tự đè lên nhau và luôn là ở góc trên cùng bên trái. Ví dụ 1 button có left margin là 100 và 1 button bình
//thường khi ta render lên độc lập bth trong 1 page thì cả 2 button vẫn trùng nhau ở góc trên cùng bên trái. Chỉ có
//điểm khác biệt là button đầu có leftMargin bằng 100 nhưng phần 100 đó tràn ra ngoài màn hình chả nhìn thấy nên vị trí
//nó vẫn ở đó. Do đó bố cục 1 page hiển thị được ta phải cho chúng có quan hệ với nhau bằng anchors và column, row,
//grid,..
//Thuộc tính trong phần list all nó éo đủ.
//Chú ý trap năng là dùng id thì truy cập được vào mọi thuộc tính của các element khác kể cả con của sibling nhưng
//k lấy được các thuộc tính anchors như bottom, right,..
//Ví dụ để set 1 button dưới 1 phần text trong 1 page. Ta có thể set y của button đó là height của text or ta dùng
//anchors top của button ngay dưới text or dùng anchor top của button là top page xong set margin của button là
//height của text(muốn dùng topMargin bắt buộc phải có anchors top).
//Tuy nhiên nếu text lại nằm trong 1 column thì button khi anchor ta phải anchor theo column nhưng nếu Component bao
//ngoài text có kích thước k theo con vd như FocusScope luôn ở top left mặc dù con nó rộng vl thì cách dùng anchor
//sẽ k hđ, khi đó vẫn có thể lấy kích thước của con gán cho cha r anchor theo focusScope => nch là kiểu gì cx sẽ sắp
//đc vị trí dựa vào kích thước or anchor tùy TH ta phải làm cho đúng
Page {
    id: page3
    title: "Page 3: Learn Focus"
    FocusScope{
        id: focusScope
        height: textField.height
        Column{
            AppTextField{
                id: textField
                width: page3.width
                focus: true

                //bàn phím có 4 phím move
                KeyNavigation.down: textField2
                //khi cho như này mà k set gì ở trong textField2 nó sẽ tự hiểu ngược lại phím lên sẽ quay lại cái này
                //tương tự với các phím khác
            }
            AppTextField{
                id: textField2
                width: page3.width
                focus: true

                //thao tác với bàn phím,KeyNavigation chỉ có 4 phím nhưng Keys thì mọi phím.Là QML Type bth nhưng
                //truy cập được luôn thuộc tính kiểu này vì Keys và KeyNavigation là global bắt signal keyboard mọi lúc
                Keys.onReturnPressed: textField.forceActiveFocus()
                Keys.onLeftPressed: textField.forceActiveFocus()//k lùi thanh gõ chữ sang trái bằng phím left đc nx
                //ví dụ điều khiển nhân vật di sang trái. Nhưng dù sao cái này cx chỉ có ích trên desktop chứ vô dụng
                //với mobile
            }
        }
    }
    Column{
        anchors.centerIn: parent
        AppButton{
            text: "Use forceActiveFocus"
            onClicked: {
                console.log(focusScope.focus)
                textField.forceActiveFocus()
            }
        }
        AppButton{
            text: "Use FocusScope"
            onClicked: {
                focusScope.forceActiveFocus()
//                focusScope.focus = true//cx đc
            }
        }
    }

}
//activeFocus là readonly nếu 1 component đang được focus vào thì sẽ true, còn forceActiveFocus sẽ focus vào 1 component
//làm cho activeFocus là true.
//Ta kbh focus đc 2 thứ cùng 1 lúc, nếu 1 cái đang activeFocus thì các cái khác sẽ có activeFocus là true

//Tuy nhiên ng ta đẻ ra 1 cái khác nx là FocusScope. Thật ra cái này k cần thiết cx đc. Khi dùng nó thì khi ta gọi
//focus vào nó or gán focus bằng true đều đc thì nó sẽ focus vào 1 con của nó có thuộc tính focus = true. nếu có nh
//con như v thì sẽ focus vào con nào đc focus ở lần cuối cùng or nếu tát cả đều là lần đầu tiên thì focus vào con đc
//render cuối cùng(vì nó chỉ focus đc vào 1 thứ mà thôi)

//Dùng FocusScope cx chỉ như là dùng Item nên rất thoải mái, nó giống hệt item chỉ là có thêm tác dụng trên thôi

//Khi ta có keyboard 4 phím di chuyển thì có thể dùng Key để focus or mặc định cx có phim tab r.

//Nch là dùng với phone thì chỉ cần forceActiveFocus() là ok r
