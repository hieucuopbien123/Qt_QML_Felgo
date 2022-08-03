import QtQuick 2.0
import Felgo 3.0
import QtGraphicalEffects 1.0
import QtQuick.Controls 2.4

FlickablePage {
    useSafeArea: false
    title: "Giới thiệu"
    id: introPage
    flickable.contentHeight: col.height
    scrollIndicator.visible: true

    rightBarItem: NavigationBarRow{
        ActivityIndicatorBarItem{
            visible: dataModel.loading
        }
        IconButtonBarItem{
            icon: IconType.heart
            onClicked: {
                navigationStack.push(favouriteComponent,{isFavourite: true})
                clickSound.play()
            }
        }
        SoundEffect {
             id: clickSound
             source: "../../assets/jkl.wav"
         }
    }
    Component{
        id: favouriteComponent
        ListBlogContentPage{ }
    }

    Column{
        id: col
        width: parent.width
        spacing: 20
        Rectangle{
            width: parent.width
            height: introText.height*1.5
            AppImage{
                id: appimage
                fillMode: Image.PreserveAspectCrop
                width: parent.width
                clip: true
                z: -1
                source: "../../assets/intro.jpg"
                height: parent.height
            }
            ColorOverlay {
                anchors.fill: appimage
                source: appimage
                color: "#80000000"
            }
            AppText{
                anchors.centerIn: parent
                id: introText
                font.pixelSize: sp(20)
                font.family: "Helvetica"
                text: "Xin cảm ơn quý bạn đã sử dụng <strong>Love hands</strong>. Chúng tôi hy vọng ứng dụng sẽ mang lại cho\
 quý bạn những phút giây thư giãn và những kiến thức bổ ích."
                width: parent.width - contentPadding*2
                wrapMode: Text.WrapAtWordBoundaryOrAnywhere
                color: "white"
                z: 1
                horizontalAlignment: Qt.AlignHCenter
                verticalAlignment: Qt.AlignVCenter
            }
        }
        Rectangle{
            width: parent.width
            height: swipeView.height
            SwipeView {
                id: swipeView
                width: parent.width
                height: itemview2.height

                Item{
                    id: itemview
                    width: introPage.width
                    height: paper.height
                    AppPaper{
                        id: paper
                        anchors.centerIn: parent
                        width: introPage.width - contentPadding*2
                        height: paper2.height
                        radius: dp(4)
                        AppButton{
                            y: contentPadding
                            id: icon
                            icon: IconType.hearto
                            x: paper.width/2 - width/2
                            width: dp(45)
                            height: width
                            radius: width/2
                            minimumHeight: 0
                            minimumWidth: 0
                            horizontalPadding: 0
                            verticalPadding: 0
                            horizontalMargin: 0
                            verticalMargin: 0
                            backgroundColor: "green"
                            backgroundColorPressed: "green"
                        }
                        AppText{
                            id: text
                            text: "SỨ MỆNH"
                            color: "darkgreen"
                            anchors.top: icon.bottom
                            anchors.horizontalCenter: parent.horizontalCenter
                            anchors.topMargin: contentPadding/2
                        }
                        AppText{
                            id: content
                            text: "Tham gia chăm sóc sức khỏe cộng đồng."
                            color: "darkgreen"
                            anchors.top: text.bottom
                            anchors.horizontalCenter: parent.horizontalCenter
                            anchors.topMargin: contentPadding/2
                            width: parent.width - contentPadding*2
                            wrapMode: Text.WrapAtWordBoundaryOrAnywhere
                            horizontalAlignment: Qt.AlignHCenter
                        }
                    }
                }
                Item{
                    id: itemview2
                    width: introPage.width
                    height: paper2.height
                    AppPaper{
                        id: paper2
                        anchors.centerIn: parent
                        width: introPage.width - contentPadding*2
                        height: icon2.height + text2.height + content2.height + icon2.y + text2.anchors.topMargin +
                                content2.anchors.topMargin + contentPadding*2
                        radius: dp(4)
                        AppButton{
                            y: contentPadding
                            id: icon2
                            icon: IconType.eye
                            x: paper.width/2 - width/2
                            width: dp(45)
                            height: width
                            radius: width/2
                            minimumHeight: 0
                            minimumWidth: 0
                            horizontalPadding: 0
                            verticalPadding: 0
                            horizontalMargin: 0
                            verticalMargin: 0
                            backgroundColor: "green"
                            backgroundColorPressed: "green"
                        }
                        AppText{
                            id: text2
                            text: "TẦM NHÌN"
                            color: "darkgreen"
                            anchors.top: icon2.bottom
                            anchors.horizontalCenter: parent.horizontalCenter
                            anchors.topMargin: contentPadding/2
                        }
                        AppText{
                            id: content2
                            text: "Trong 5 năm  tới hoàn thiện hệ thống  và phương pháp chữa bệnh độc đáo của y học dân\
 gian Việt Nam, giúp đỡ và chăm sóc sức khỏe cho 500,000 người. từng  bước giới thiệu ra thị trường Nhật, Hàn, Trung\
 Quốc."
                            color: "darkgreen"
                            anchors.top: text2.bottom
                            anchors.horizontalCenter: parent.horizontalCenter
                            anchors.topMargin: contentPadding/2
                            width: parent.width - contentPadding*2
                            wrapMode: Text.WrapAtWordBoundaryOrAnywhere
                            horizontalAlignment: Qt.AlignHCenter
                        }
                    }
                }
                Item{
                    id: itemview3
                    width: introPage.width
                    height: paper3.height
                    AppPaper{
                        id: paper3
                        anchors.centerIn: parent
                        width: introPage.width - contentPadding*2
                        height: paper2.height
                        radius: dp(4)
                        AppButton{
                            y: contentPadding
                            id: icon3
                            icon: IconType.fire
                            x: paper3.width/2 - width/2
                            width: dp(45)
                            height: width
                            radius: width/2
                            minimumHeight: 0
                            minimumWidth: 0
                            horizontalPadding: 0
                            verticalPadding: 0
                            horizontalMargin: 0
                            verticalMargin: 0
                            backgroundColor: "green"
                            backgroundColorPressed: "green"
                        }
                        AppText{
                            id: text3
                            text: "KHẨU HIỆU"
                            color: "darkgreen"
                            anchors.top: icon3.bottom
                            anchors.horizontalCenter: parent.horizontalCenter
                            anchors.topMargin: contentPadding/2
                        }
                        AppText{
                            id: content3
                            text: "Sẻ chia hiểu biết, nhận về niềm vui - Share knowledge, get happiness."
                            color: "darkgreen"
                            anchors.top: text3.bottom
                            anchors.horizontalCenter: parent.horizontalCenter
                            anchors.topMargin: contentPadding/2
                            width: parent.width - contentPadding*2
                            wrapMode: Text.WrapAtWordBoundaryOrAnywhere
                            horizontalAlignment: Qt.AlignHCenter
                        }
                    }
                }
             }
            PageIndicator {
                id: indicator

                count: swipeView.count
                currentIndex: swipeView.currentIndex

                anchors.bottom: swipeView.bottom
                anchors.horizontalCenter: parent.horizontalCenter
            }
            //2 vấn đề: 1 là Rectangle bao ngoài swipeview thì phải set rõ ràng cả width và height thì height
            //của Rectangle sẽ mãi mãi là 0-> đúng là v vì column đúng là nó tự mở rộng theo con vì nó là 1
            //container layout, còn Rectangle là 1 hình vẽ hiển thị k có vai trò bao commponent khác nên kích
            //thước sẽ là 0. Khi parent có kích thước là 0 thì con sẽ k thể theo parent mà sẽ quay về gốc 0,0 của màn
            //hình và đó là 1 lỗi chứ kp ở nguyên gốc 0,0 của parent đâu.
            //2 là PageIndicator phải dùng ngoài swipeview. Ta cần set tổng count và từng vị trí index bằng bind
            //là ta được 1 cái indicator rồi, ta cần đặt nó ở vị trí nào thì chỉnh như trên với anchors
            //Nếu dùng ở trong swipe view thì nó coi đó là 1 item nx trong swipe view vì mỗi component khác trong
            //swipe view đều là 1 item riêng của nó như v. Và ta cx phải đặt nó trong 1 Component bên ngoài nx
            //vì nếu k thì nó sẽ nằm trong 1 column mà column có quy tắc là nối tiếp nhau theo kc là spacing nên
            //lúc đó k thể anchors đổi vị trí đc nx mà phải theo quy tắc của column

            //Vấn đề nx là tại sao cái indicator lại dùng anchor horizontalCenter với parent chứ kp với swipe view
            // Nên nhớ rằng swipeView có width phải luôn là động được gán theo cha, tức là có quan hệ với parent
            //width, nếu ta gán fix 1 số vd 400 sẽ lỗi vì nó đơn giản k nhận thôi. Nếu ta gán kiểu parent.width + 10
            //thì width của SwipeView là width của từng Item trong SwipeView đó thì ở đây 1 page dài quá màn hình
            //10px. Nếu ta gán Indicator horizontalCenter theo swipe thì sẽ lệch sang phải 5px vì nó nằm ở trung
            //điểm 1 item mà. Nếu ta muốn kc nó xa hơn mà indicator gán đc như thế thì có thể tách ra width theo
            //parent.width và spacing = 10 => tức cái phạm vi hiển thị 1 item trong swipe view chính là kích thước
            //swipeview đó
        }
//        AppText{
//            id: detailTitle
//            text: "Câu chuyện về chiếc xe chúng ta đang đi"
//        }
//        AppText{
//            id: detailContent
//            text: "Chiếc xe hàng ngày chúng ta đi vẫn được định kỳ bảo dưỡng để đảm bảo an toàn. Nút giao thông vẫn\
// có những cột đèn để tránh ùn tắc và để ta chậm lại vài giây nghĩ về chặng đường đã qua.Vậy đã bao giờ bạn nghĩ\
// rằng, liệu chúng ta có cần chậm lại để bảo dưỡng định kỳ không nhỉ?Câu chuyện về chiếc xe chúng ta đang đi"
//        }
        AppCard{
            id: card1
            //thay vì bao ngoài 1 Component khác ta dùng margin phát là xong
            width: parent.width//width bth như này có tính cả padding, margin
            paper.radius: dp(10)
            margin: dp(20)
            header: SimpleRow{
                detailText: "Câu chuyện về chiếc xe chúng ta đang đi"
                style: StyleSimpleRow{
                    backgroundColor: "transparent"
                    detailTextColor: "darkgreen"
                }
            }
            content: AppText{
                text: "Chiếc xe hàng ngày chúng ta đi vẫn được định kỳ bảo dưỡng để đảm bảo an toàn. Nút giao thông\
 vẫn có những cột đèn để tránh ùn tắc và để ta chậm lại vài giây nghĩ về chặng đường đã qua. Vậy đã bao giờ bạn nghĩ\
 rằng, liệu chúng ta có cần chậm lại để bảo dưỡng định kỳ không nhỉ?"
                width: parent.width
                padding: dp(15)
            }
        }
        AppCard{
            id: card2
            width: parent.width
            paper.radius: dp(10)
            leftMargin: dp(20)
            rightMargin: dp(20)

            header: SimpleRow{
                detailText: "Và điều gì là quan trọng nhất đối với bản thân mình?"
                style: StyleSimpleRow{
                    backgroundColor: "transparent"
                    detailTextColor: "darkgreen"
                }
            }
            content: AppText{
                text: "Tiền bạc? Địa vị, Quyền lực hay những Đam mê nào đó? Xã hội đang tôn vinh những người nghĩ ra\
 cách kiếm được nhiều tiền, để kiếm được nhiều tiền thi cần lao tâm khổ trí, kết quả là đổi sức khỏe và thời gian để\
 lấy tiền. Nhưng rồi tất cả những gì bạn đạt được cũng sẽ rời bỏ khi bạn lìa đời. Khi bạn có tất cả mà không có sức\
 khỏe thì mọi thứ đều trở nên vô nghĩa."
                width: parent.width
                padding: dp(15)
            }
        }
        AppCard{
            width: parent.width
            paper.radius: dp(10)
            leftMargin: dp(10)
            rightMargin: dp(10)
            header: SimpleRow{
                text: "Lovehands"
                detailText: "Đôi bàn tay yêu thương"
                style: StyleSimpleRow{
                    backgroundColor: "transparent"
                    detailTextColor: "darkgreen"
                    textColor: "limegreen"
                }
            }
            media: AppImage{
                width: parent.width
                fillMode: Image.PreserveAspectFit
                source: "https://lovehands.vn/wp-content/uploads/2021/07/doi-ban-tay-yeu-thuong.jpg"
            }

            content: Item{
                width: parent.width
                height: childrenRect.height
                Column{
                    width: parent.width
                    AppText{
                        text: "Thuận lẽ tự nhiên"
                        color: "darkgreen"
                        width: parent.width
                        padding: dp(15)
                    }
                    AppText{
                        text: "Trong bối cảnh hiện tại của nước ta, ngành Y - Dược phát triển mạnh mẽ và đã làm chủ\
 được nhiều công nghệ hiện đại. Tuy nhiên chúng ta hãy thẳng thắn nhìn vào thực trạng hiện nay khi bệnh hiểm nghèo\
 ngày càng gia tăng thì đa số người bệnh vẫn chưa đủ điều kiện để tiếp cận các dịch vụ y tế tại nhà như các nước\
 phát triển. Chúng tôi thấy rằng những kiến thức y học dân gian được đúc kết từ hàng nghìn đời nay và đã trải qua\
 thực nghiệm thì cần phải được cóp nhặt lại và phổ biến đến từng người dân Việt và đồng bào mình được hưởng chính\
 những thành quả của ông cha ta đã gieo trồng từ bao đời nay, các kiến thức này cần được công khai để phục vụ lợi\
 ích của cả cộng đồng, như vậy cũng thuận lẽ tự nhiên."
                        color: "black"
                        width: parent.width
                        leftPadding: dp(10)
                        rightPadding: dp(10)
                    }
                    AppText{
                        text: "Mong muốn nhỏ nhoi"
                        color: "darkgreen"
                        width: parent.width
                        padding: dp(15)
                    }
                    AppText{
                        text: "Chúng tôi - những người xây dựng Ứng dụng <strong>Love hands</strong> chỉ có một mong\
 ước nhỏ bé là được đóng góp công sức, trí tuệ để những người bệnh có cơ hội được áp dụng các phương pháp chữa bệnh\
 đơn giản nhất, giảm thiểu được chi phí, để bạn có thể tự chăm sóc sức khỏe cho bản thân cũng như những người thân\
 yêu."
                        color: "black"
                        width: parent.width
                        leftPadding: dp(10)
                        rightPadding: dp(10)
                        bottomPadding: dp(10)
                    }
                }
            }
        }
        AppText{
            leftPadding: dp(15)
            rightPadding: dp(15)
            text: "Cam kết"
            anchors.horizontalCenter: parent.horizontalCenter
            font.bold: true
            color: "darkgreen"
        }
        AppText{
            leftPadding: dp(15)
            rightPadding: dp(15)
            text: "Lovehands như một cuốn sách nhỏ trong tay bạn với hàng ngàn bài thuốc, hàng trăm bài hướng dẫn tự chữa\
 bệnh, hàng trăm bài hướng dẫn làm đẹp và chăm sóc sức khỏe gia đình bạn."
            width: parent.width
        }

        Rectangle{
            width: parent.width - contentPadding*3
            height: 2
            x: contentPadding*1.5
            border.color: "limegreen"
        }

        AppText{
            anchors.horizontalCenter: parent.horizontalCenter
            text: "Độc giả viết bài"
            font.bold: true
            color: "darkgreen"
        }
        AppText{
            leftPadding: dp(15)
            rightPadding: dp(15)
            text: "Kính thưa độc giả của Lovehands, blog lovehands.vn được lập ra với mục đích chính là chia sẻ kiến thức tới\
 cộng đồng. Các bài viết tại blog của chúng tôi một phần được viết bởi Tác giả Nguyễn Văn Chí, một phần viết bởi các tác giả\
 tại các trang báo khác."
            //nếu xuống dòng sẽ k viết đc html nx
            width: parent.width
            bottomPadding: 10
        }
        Rectangle{
            width: parent.width - contentPadding*3
            height: 2
            x: contentPadding*1.5
            border.color: "limegreen"
        }

        AppText{
            leftPadding: dp(15)
            rightPadding: dp(15)
            text: "Nếu bạn là người muốn chia sẻ kiến thức và kinh nghiệm của mình tới cộng đồng, xin vui lòng gửi bài viết về\
 địa chỉ email: <b>thanhchi18@gmail.com</b>. Chúng tôi sẽ xem xét và đăng bài dưới tên tác giả là bạn. Xin cám ơn!"
            width: parent.width
            bottomPadding: 10
        }

    }

}
