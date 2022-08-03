import QtQuick 2.0
import Felgo 3.0
import QtQuick.Controls 2.4
 import QtMultimedia 5.9

FlickablePage {
    title: "Nguyễn Văn Chí"
    useSafeArea: false
    flickable.contentHeight: colu.height + colu.anchors.topMargin + contentPadding
    //chú ý height k thôi thì k tính margin
    Column{
        id: colu
        width: parent.width
        anchors.top: parent.top
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.margins: contentPadding
        spacing: dp(20)
        AppText{
            text: "Về lương y Nguyễn Văn Chí"
            font.bold: true
            color: "darkgreen"
            font.pixelSize: sp(20)
            anchors.horizontalCenter: colu.horizontalCenter
        }
       AppText{
           text:"Nguyễn Văn Chí, còn có tên gọi là Nguyễn Thành Chí (tác giả của cuốn “Mật mã Phật Sơn”); sinh\
 ngày 09/09/1980; hiện thường trú tại An Khê 1, phường Đằng Lâm, Hải An, Hải Phòng. Ông là kỹ sư thiết kế thân tàu\
 thủy, hiện là Giám đốc Công ty CP Công nghiệp Tàu thủy Đông Bắc; Ủy viên BCH Hiệp hội Những người Lao động Sáng\
 tạo Việt Nam.

 Ông còn có bằng Y sĩ Y học cổ truyền; sáng lập Công ty CP Lovehands hoạt động trong lĩnh vực chăm sóc sức khỏe cộng\
 đồng, sản xuất thiết bị trị liệu chăm sóc sức khỏe và chữa bệnh bằng Phương pháp cân bằng thân nhiệt.

 Sản phẩm của ông từng được trưng bày tại Hội nghị Tổng kết năm 2020 của Hiệp hội Những người Lao động Sáng tạo Việt\
 Nam (tổ chức ngày 12/01/2020, tại Nhà Văn hóa Thanh Xuân, Hà Nội, cùng Liên hiệp Khoa học Công nghệ thông tin ứng\
 dụng-UIA và Trung tâm Bảo tồn phát huy giá trị di sản Phật giáo)."
           wrapMode: Text.WrapAtWordBoundaryOrAnywhere
           width: parent.width
       }
       AppText{
           text: "Tác phẩm Mật mã Phật sơn"
           font.bold: true
           color: "darkgreen"
           anchors.horizontalCenter: colu.horizontalCenter
       }
       AppImage{
           source: "https://lovehands.vn/wp-content/uploads/2021/06/mat-ma-phat-son-le-thanh-chi.png"
           width: parent.width
           fillMode: Image.PreserveAspectFit
       }
       AppText{
           text:"Nguyễn Văn Chí có bút danh là Nguyễn Thành Chí (hoặc Tiểu Tuệ) là tác giả của cuốn Mật mã Phật sơn\
 viết về những khám phá bí ẩn văn hóa Phương Đông và tư vấn chăm sóc sức khỏe cộng đồng (Nxb. Hồng Đức, 2020)."
           wrapMode: Text.WrapAtWordBoundaryOrAnywhere
           width: parent.width
       }
       AppText{
           text: "Vườn thuốc nam của Lương y Nguyễn Văn Chí"
           width: parent.width
           wrapMode: Text.WrapAtWordBoundaryOrAnywhere
           font.bold: true
           color: "darkgreen"
           anchors.horizontalCenter: colu.horizontalCenter
       }
        MediaPlayer {
            id: mediaplayer
            autoPlay: true
            loops: MediaPlayer.Infinite
            source: "https://lovehands.vn/wp-content/uploads/2021/07/vuon-thuoc-nam-luong-y-nguyen-van-chi.mp4"
          }

        VideoOutput {
            id: mediao
            width: parent.width
            height: sourceRect.height / sourceRect.width * width
            source: mediaplayer
        }
        AppImage{
            source: "https://lovehands.vn/wp-content/uploads/2021/07/vuon-cay-thong-dat.jpg"
            width: parent.width
            clip: true
            fillMode: Image.PreserveAspectCrop
        }
        AppImage{
            source: "https://lovehands.vn/wp-content/uploads/2021/07/vuon-thuoc-nam-luong-y-nguyen-van-chi.jpg"
            width: parent.width
            fillMode: Image.PreserveAspectCrop
        }
        AppImage{
            source: "https://lovehands.vn/wp-content/uploads/2021/07/vuon-thuoc-nam-cua-luong-y-nguyen-van-chi-2.jpg"
            width: parent.width
            fillMode: Image.PreserveAspectCrop
        }
    }
}
