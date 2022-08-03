import QtQuick 2.0
import Felgo 3.0

FlickablePage {
    useSafeArea: true
    title: "Liên hệ"
    flickable.contentHeight: colu.height
    scrollIndicator.visible: true
    //để tạo khoảng cách cho app éo ai đi set padding cho từng cái cả mà làm luôn ở cái layout ngoài cùng
    Column{
        id: colu
        width: parent.width
        anchors.top: parent.top
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.margins: contentPadding
        spacing: contentPadding
        AppText{
            id: appTextContact
            text: "Công ty cổ phần Lovehands."
            color: "green"
            font.bold: true
            x: parent.width/2 - width/2
        }

        Grid{
            width: parent.width
            columns: 2
            spacing: dp(10)
            Icon{
                id: icon1
                icon: IconType.mapmarker
                color: "green"
            }
            AppText{
                text: "Số 18, Ngõ 281, Đường Cát Bi, Phường Cát Bi, Quận Hải An, Tp Hải Phòng"
                width: parent.width - icon1.width - contentPadding
                wrapMode: Text.WrapAtWordBoundaryOrAnywhere
            }
            //có cái Column anchor rồi thì bên trong phải tự hiểu làm thế nào để hiển thị cách 2 mép 1 đoạn
            //dù grid có thế nào thì text nó tự in tràn mà nên phải set width chuẩn phạm vi của nó
            //cái width của colu bị co lại ở TH này vì k tính margin
            Icon{
                id: icon2
                icon: IconType.phone
                color: "green"
            }
            AppText{
                text: "Hotline: 083 66 99 188"
                width: contactPage.width - icon2.width - contentPadding
                wrapMode: Text.WrapAtWordBoundaryOrAnywhere
            }
            Icon{
                id: icon3
                icon: IconType.envelope
                color: "green"
            }
            AppText{
                text: "E-mail: thanhchi18@gmail.com"
                width: contactPage.width - icon3.width - contentPadding
                wrapMode: Text.WrapAtWordBoundaryOrAnywhere
            }
        }
    }
}
