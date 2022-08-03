import QtQuick 2.0
import Felgo 3.0
import QtQuick.Controls 2.4

FlickablePage {
    title: "Trang chủ"
    id: mainPage
    flickable.contentHeight: col.height
    scrollIndicator.visible: true
    rightBarItem: NavigationBarRow{
        ActivityIndicatorBarItem{
            visible: dataModel.loading
        }
        IconButtonBarItem{
            icon: IconType.heart
            onClicked: {
                navigationStack.popAllExceptFirstAndPush(favouriteComponent,{isFavourite: true})
                clickSound.play()
            }
        }
        SoundEffect {
             id: clickSound
//             muted: true
             source: "../../assets/jkl.wav"
         }
        //âm thanh phải là wav. Nếu là mp3 thì phải dùng BackgroundMusic(cho nhạc).
        //đôi lúc wav bị lỗi phải convert sang mp3 r lại convert lại
    }
    Component{
        id: favouriteComponent
        ListBlogContentPage{ }
    }

    Column {
        id:col
         width: parent.width

//         Rectangle{
//             id: qwsWrapper
//             height: dp(300)
//             width: parent.width
//             Rectangle {
//               width: bannerImage.width
//               height: bannerImage.height
//               anchors.bottom: parent.bottom
//               color: "white"
//             }
//             Rectangle {
//               id: bannerImage
//               width: parent.width
//               anchors.bottom: parent.bottom
//               height: mainPage.flickable.contentY < 0 ? qwsWrapper.height - mainPage.flickable.contentY : qwsWrapper.height
//               //contentY mang giá trị âm khi flick xuống nx, ta gắn bottom nó fix r tăng height là tự mở
//               color: "limegreen"
//               opacity: 0.7
//               gradient: Gradient {
//                 GradientStop { position: 0.0; color: "#13fb2f" }
//                 GradientStop { position: 1.0; color: "#0041cd52" }
//               }
//             }

//             Rectangle {
//               opacity: 0.5
//               anchors.centerIn: bannerImage
//               height: bannerImage.width
//               width: bannerImage.height
//               rotation: -90
//               transformOrigin: Item.Center
//               gradient: Gradient {
//                 GradientStop { position: 0.0; color: "#41cd52" }
//                 GradientStop { position: 1.0; color: "#0041cd52" }
//               }
//             }


//           Column {
//             width: parent.width
//             anchors.verticalCenter: parent.verticalCenter
//             spacing: dp(Theme.navigationBar.defaultBarItemPadding)

//             AppText {
//               width: parent.width
//               horizontalAlignment: AppText.AlignHCenter
//               color: "darkgreen"
//               text: "Love hands"
//               font.bold: true
//               font.pixelSize: sp(22)
//             }

//             AppImage {
//               anchors.horizontalCenter: parent.horizontalCenter
//               source: "../../assets/lovehands-logo-100x90.png"
//               width: sourceSize.width
//               height: sourceSize.height
//               fillMode: AppImage.PreserveAspectFit
//             }

//             AppText {
//               width: parent.width
//               horizontalAlignment: AppText.AlignHCenter
//               color: "darkgreen"
//               text: "Đôi bàn tay yêu thương"
//               font.pixelSize: sp(14)
//             }
//           }
//         }
         AppText {
            width: parent.width
            topPadding: contentPadding
            bottomPadding: contentPadding
            horizontalAlignment: AppText.AlignHCenter
            color: "darkgreen"
            text: "Love hands"
            font.bold: true
            font.pixelSize: sp(22)
          }

          AppImage {
            anchors.horizontalCenter: parent.horizontalCenter
            source: "../../assets/logo.jpg"
            width: sourceSize.width
            height: sourceSize.height
            fillMode: AppImage.PreserveAspectFit
          }

          AppText {
            topPadding: contentPadding
            bottomPadding: contentPadding
            width: parent.width
            horizontalAlignment: AppText.AlignHCenter
            color: "darkgreen"
            text: "Đôi bàn tay yêu thương"
            font.pixelSize: sp(14)
          }

         //k thể col lồng col TT đc
         AppText{
             text: "Kiến thức cần biết"
             font.bold: true
             color: "darkgreen"
             font.pixelSize: sp(20)
             anchors.horizontalCenter: col.horizontalCenter
             topPadding: contentPadding
             bottomPadding: contentPadding
         }

//         Rectangle {
//             id: rec
//             width: parent.width;
//             height: dp(150)

//             Component {
//                 id: delegate
//                 Column {
//                     id: wrapper
//                     width: rec.width - contentPadding*2
//                     AppButton{
//                         text: textT
//                         flat: true
//                         textColor: "darkgreen"
//                         textColorPressed: "limegreen"
//                         rippleEffect: false
//                         opacity: wrapper.PathView.isCurrentItem
//                         Behavior on opacity {
//                             NumberAnimation { duration: 2000 }
//                         }
//                         minimumHeight: 0
//                         verticalPadding: 0
//                         onClicked: {
//                             navigationStack.popAllExceptFirstAndPush(listBlogComp)
//                         }
//                     }
//                     Component{
//                         id: listBlogComp
//                         ListBlogPage{ }
//                     }

//                     AppText {
//                         id: nameText
//                         text: detailText
//                         color: wrapper.PathView.isCurrentItem ? "green" : "black"
//                         opacity: wrapper.PathView.isCurrentItem
//                         Behavior on opacity {
//                             NumberAnimation { duration: 2000 }
//                         }
//                         wrapMode: Text.WrapAtWordBoundaryOrAnywhere
//                         width: parent.width
//                     }
//                 }
//             }
//             ListModel{
//                 id: modelList
//                 ListElement{
//                     textT: "1. Thiền"
//                     detailText: "Thiền là một cách tắt những chương trình chạy ngầm để cơ thể và tâm hồn nghỉ\
// dưỡng đấy những bạn ạ."
//                 }
//                 ListElement{
//                     textT: "2. Làm đẹp"
//                     detailText: "Đẹp giúp chúng ta tự tin hơn trong cuộc sống. Có câu “Không có người phụ nữ\
// xấu, chỉ có người phụ nữ không biết làm đẹp mình”."
//                 }
//                 ListElement{
//                     textT: "3. Làm giàu"
//                     detailText: "Làm giàu là điều mà chúng ta luôn thực hiện trong cuộc đời mình. Thời trẻ\
// làm giàu về vật chất, về già lại muốn làm giàu về sức khỏe."
//                 }
//                 ListElement{
//                     textT: "4. Ẩm thực"
//                     detailText: "Mọi thứ chúng ta ăn vào đều chuyển hóa thành năng lượng nuôi dưỡng cơ thể.\
// Năng lượng đó là tích cực hay tiêu cực phụ thuộc vào món ăn và thức uống mà chúng ta sử dụng."
//                 }
//                 ListElement{
//                     textT: "5. Giải trí"
//                     detailText: "Giải trí đúng cách sẽ giúp bạn có được tinh thần tốt, một tâm thế tốt để\
//giải quyết công việc hàng ngày."
//                 }
//                 ListElement{
//                     textT: "6. Học"
//                     detailText: "Bạn có thể học từ người thầy của mình, hoặc từ một người thành đạt, bạn\
// cũng có thể học từ bạn bè, từ đồng nghiệp và thậm chí từ những người lao công hay chú bảo vệ."
//                 }
//                 ListElement{
//                     textT: "7. Tâm linh"
//                     detailText: "Có nhiều góc nhìn về tâm linh khác nhau, mỗi góc nhìn sẽ cho bạn một khái\
// nhiệm riêng biệt."
//                 }
//                 ListElement{
//                     textT: "8. Bệnh người già"
//                     detailText: "Có nhiều góc nhìn về tâm linh khác nhau, mỗi góc nhìn sẽ cho bạn một khái\
// nhiệm riêng biệt."
//                 }
//                 ListElement{
//                     textT: "9. Bệnh trẻ em"
//                     detailText: "Có nhiều góc nhìn về tâm linh khác nhau, mỗi góc nhìn sẽ cho bạn một khái\
// nhiệm riêng biệt."
//                 }
//                 ListElement{
//                     textT: "10. Bệnh thường gặp"
//                     detailText: "Có nhiều góc nhìn về tâm linh khác nhau, mỗi góc nhìn sẽ cho bạn một khái\
// nhiệm riêng biệt."
//                 }
//             }
//             PathView {
//                 id: view
//                 anchors.fill: parent
//                 model: modelList
//                 delegate: delegate
//                 path: Path {
//                     startX: view.width/2; startY: 75
//                     PathLine{x: view.width*3; y: 0}
//                     PathLine{x: view.width/2; y: -75}
//                     PathLine{x: -view.width*2; y: 0}
//                     PathLine{x: view.width/2; y: 75}
//                 }
//             }
//         }
         //dùng các kiểu view này k nên bao nó với hcn như này mà nên dùng full anchors-> set anchors của PathView
         //top là bottom component trên và bottom là top component dưới


//         Rectangle {
//             id: rec
//             width: parent.width;
//             height: dp(150)
//             ListModel{
//                 id: modelList
//                 ListElement{
//                     textT: "1. Thiền"
//                     detailText: "Thiền là một cách tắt những chương trình chạy ngầm để cơ thể và tâm hồn nghỉ\
// dưỡng đấy những bạn ạ."
//                 }
//                 ListElement{
//                     textT: "2. Làm đẹp"
//                     detailText: "Đẹp giúp chúng ta tự tin hơn trong cuộc sống. Có câu “Không có người phụ nữ\
// xấu, chỉ có người phụ nữ không biết làm đẹp mình”."
//                 }
//                 ListElement{
//                     textT: "3. Làm giàu"
//                     detailText: "Làm giàu là điều mà chúng ta luôn thực hiện trong cuộc đời mình. Thời trẻ\
// làm giàu về vật chất, về già lại muốn làm giàu về sức khỏe."
//                 }
//                 ListElement{
//                     textT: "4. Ẩm thực"
//                     detailText: "Mọi thứ chúng ta ăn vào đều chuyển hóa thành năng lượng nuôi dưỡng cơ thể.\
// Năng lượng đó là tích cực hay tiêu cực phụ thuộc vào món ăn và thức uống mà chúng ta sử dụng."
//                 }
//                 ListElement{
//                     textT: "5. Giải trí"
//                     detailText: "Giải trí đúng cách sẽ giúp bạn có được tinh thần tốt, một tâm thế tốt để\
//giải quyết công việc hàng ngày."
//                 }
//                 ListElement{
//                     textT: "6. Học"
//                     detailText: "Bạn có thể học từ người thầy của mình, hoặc từ một người thành đạt, bạn\
// cũng có thể học từ bạn bè, từ đồng nghiệp và thậm chí từ những người lao công hay chú bảo vệ."
//                 }
//                 ListElement{
//                     textT: "7. Tâm linh"
//                     detailText: "Có nhiều góc nhìn về tâm linh khác nhau, mỗi góc nhìn sẽ cho bạn một khái\
// nhiệm riêng biệt."
//                 }
//                 ListElement{
//                     textT: "8. Bệnh người già"
//                     detailText: "Có nhiều góc nhìn về tâm linh khác nhau, mỗi góc nhìn sẽ cho bạn một khái\
// nhiệm riêng biệt."
//                 }
//                 ListElement{
//                     textT: "9. Bệnh trẻ em"
//                     detailText: "Có nhiều góc nhìn về tâm linh khác nhau, mỗi góc nhìn sẽ cho bạn một khái\
// nhiệm riêng biệt."
//                 }
//                 ListElement{
//                     textT: "10. Bệnh thường gặp"
//                     detailText: "Có nhiều góc nhìn về tâm linh khác nhau, mỗi góc nhìn sẽ cho bạn một khái\
// nhiệm riêng biệt."
//                 }
//             }
//             SwipeView {
//                 id: swipeView
//                 anchors.fill: parent
//                 Repeater{
//                     model: modelList
//                     Column {
//                         id: wrapper
//                         width: rec.width
//                         AppButton{
//                             text: model.textT
//                             flat: true
//                             textColor: "darkgreen"
//                             textColorPressed: "limegreen"
//                             rippleEffect: false
//                             minimumHeight: 0
//                             verticalPadding: 0
//                             onClicked: {
//                                 navigationStack.popAllExceptFirstAndPush(listBlogComp)
//                             }
//                             horizontalMargin: contentPadding
//                         }
//                         Component{
//                             id: listBlogComp
//                             ListBlogPage{ }
//                         }

//                         AppText {
//                             id: nameText
//                             text: model.detailText
//                             color: wrapper.PathView.isCurrentItem ? "green" : "black"
//                             wrapMode: Text.WrapAtWordBoundaryOrAnywhere
//                             width: parent.width
//                             leftPadding: contentPadding
//                             rightPadding: contentPadding
//                         }
//                     }
//                 }
//             }
//             PageIndicator {
//                 id: indicator

//                 count: modelList.count
//                 currentIndex: swipeView.currentIndex

//                 anchors.bottom: swipeView.bottom
//                 anchors.horizontalCenter: parent.horizontalCenter
//             }
//         }


              ListModel{
                  id: modelList
                  ListElement{
                      text: "1. Thiền"
                      detailText: "Thiền là một cách tắt những chương trình chạy ngầm để cơ thể và tâm hồn nghỉ\
  dưỡng đấy những bạn ạ."
                  }
                  ListElement{
                      text: "2. Làm đẹp"
                      detailText: "Đẹp giúp chúng ta tự tin hơn trong cuộc sống. Có câu “Không có người phụ nữ\
  xấu, chỉ có người phụ nữ không biết làm đẹp mình”."
                  }
                  ListElement{
                      text: "3. Làm giàu"
                      detailText: "Làm giàu là điều mà chúng ta luôn thực hiện trong cuộc đời mình. Thời trẻ\
  làm giàu về vật chất, về già lại muốn làm giàu về sức khỏe."
                  }
                  ListElement{
                      text: "4. Ẩm thực"
                      detailText: "Mọi thứ chúng ta ăn vào đều chuyển hóa thành năng lượng nuôi dưỡng cơ thể.\
  Năng lượng đó là tích cực hay tiêu cực phụ thuộc vào món ăn và thức uống mà chúng ta sử dụng."
                  }
                  ListElement{
                      text: "5. Giải trí"
                      detailText: "Giải trí đúng cách sẽ giúp bạn có được tinh thần tốt, một tâm thế tốt để\
 giải quyết công việc hàng ngày."
                  }
                  ListElement{
                      text: "6. Học"
                      detailText: "Bạn có thể học từ người thầy của mình, hoặc từ một người thành đạt, bạn\
  cũng có thể học từ bạn bè, từ đồng nghiệp và thậm chí từ những người lao công hay chú bảo vệ."
                  }
                  ListElement{
                      text: "7. Tâm linh"
                      detailText: "Có nhiều góc nhìn về tâm linh khác nhau, mỗi góc nhìn sẽ cho bạn một khái\
  nhiệm riêng biệt."
                  }
                  ListElement{
                      text: "8. Bệnh người già"
                      detailText: "Có nhiều góc nhìn về tâm linh khác nhau, mỗi góc nhìn sẽ cho bạn một khái\
  nhiệm riêng biệt."
                  }
                  ListElement{
                      text: "9. Bệnh trẻ em"
                      detailText: "Có nhiều góc nhìn về tâm linh khác nhau, mỗi góc nhìn sẽ cho bạn một khái\
  nhiệm riêng biệt."
                  }
                  ListElement{
                      text: "10. Bệnh thường gặp"
                      detailText: "Có nhiều góc nhìn về tâm linh khác nhau, mỗi góc nhìn sẽ cho bạn một khái\
  nhiệm riêng biệt."
                  }
              }

           AppListView{
               width: parent.width
               height: contentHeight
               model: modelList
               boundsBehavior: Flickable.StopAtBounds
               flickableDirection: Flickable.HorizontalFlick
               delegate:SwipeOptionsContainer{
                   SimpleRow{
                    showDisclosure: true
                    style: StyleSimpleRow{
                        textColor: "darkgreen"
                        selectedBackgroundColor: "limegreen"
                        disclosureColor: "darkgreen"
                    }
                    onSelected: {
                            navigationStack.popAllExceptFirstAndPush(listBlogComp)
                     }
                    item: modelList.get(index)
                   }
               }
           }
           Component{
               id: listBlogComp
               ListBlogPage{ }
           }
           //mấy cái view mà k set kích thước thì chỉ có chết
           //điểm khác biệt là AppListView có scrollIndicator, còn listview thì k
           //còn ListPage là biến cả cái này là 1 page nằm dưới các component khác chứ k bị ảnh hướng bởi column
           //nó tự có flickable, điều khiển với flickableDirection
           //Nếu sẻ height = contentHeight + chỉnh sửa boundsBehaviour như trên là ok nhưng với 1 số điện thoại màn
           //hình to nó éo đúng-> cho thành ngang
           //Và flick nó còn cho các padding của text rất ok tự căn chỉnh r còn đường kẻ lại full
           //dùng SwipeOptionsContainer cho đỡ flick v

         AppCard{
             width: parent.width
             paper.radius: dp(10)
             topMargin: contentPadding
             leftMargin: contentPadding
             rightMargin: contentPadding
             bottomMargin: contentPadding
             header: SimpleRow{
                 text: "Đôi lời tản mạn"
                 detailText: "Đôi bàn tay yêu thương"
                 style: StyleSimpleRow{
                     backgroundColor: "transparent"
                     detailTextColor: "darkgreen"
                     selectedBackgroundColor: "limegreen"
                     textColor: "limegreen"
                 }
                 onSelected:{
                     navigationStack.popAllExceptFirstAndPush(introComp)
                 }
             }
             media: AppImage{
                 width: parent.width
                 fillMode: Image.PreserveAspectFit
                 source: "https://lovehands.vn/wp-content/uploads/2021/06/gioi-thieu-lovehands.jpg"
             }

             content: Item{
                 width: parent.width
                 height: childrenRect.height
                 Column{
                     width: parent.width
                     AppText{
                         text: "Tôi không phải là một người viết lách chuyên nghiệp. Tôi chỉ là một người mạo muội\
 xin được chấp bút viết về những kiến thức y học nhằm giúp đỡ cộng đồng."
                         color: "darkgreen"
                         font.bold: true
                         width: parent.width
                         padding: dp(15)
                     }
                     AppText{
                         text: "Quan điểm của tôi là “Sống là để chia sẻ”, những kiến thức mà bản thân mình biết\
 nếu không chia sẻ và biến nó thành hành động thì sẽ sớm chôn vùi vào quên lãng."
                         color: "black"
                         width: parent.width
                         leftPadding: dp(10)
                         rightPadding: dp(10)
                     }
                 }
             }
             actions: AppButton{
                 width: parent.width
                 text: "Giới thiệu"
                 textColor: "green"
                 backgroundColorPressed: "green"
                 radius: dp(20)
                 backgroundColor: "transparent"
                 borderColor: "green"
                 borderWidth: 2
                 onClicked: {
                     navigationStack.popAllExceptFirstAndPush(introComp)
                 }
             }
             Component{
                 id: introComp
                 IntroPage{ }
             }
         }
         AppCard{
             width: parent.width
             paper.radius: dp(10)
             leftMargin: contentPadding
             rightMargin: contentPadding
             bottomMargin: contentPadding
             header: SimpleRow{
                 text: "Sản phẩm"
                 detailText: "Thiết bị trị liệu"
                 style: StyleSimpleRow{
                     backgroundColor: "transparent"
                     selectedBackgroundColor: "limegreen"
                     detailTextColor: "darkgreen"
                     textColor: "limegreen"
                 }
                 onSelected: {
                     navigationStack.popAllExceptFirstAndPush(productComp)
                 }
             }
             content: Item{
                 width: parent.width
                 height: childrenRect.height
                 Column{
                     width: parent.width
                     AppText{
                         text: "Thiết bị vật lý trị liệu của Lovehands là sự kết hợp giữa Đông y và Khoa học Công\
 nghệ, do Lương y Nguyễn Văn Chí chế tạo giúp chữa nhiều loại bệnh khác nhau."
                         color: "black"
                         width: parent.width
                         leftPadding: dp(10)
                         rightPadding: dp(10)
                     }
                 }
             }
             actions: AppButton{
                 width: parent.width
                 text: "Sản phẩm"
                 textColor: "green"
                 backgroundColorPressed: "green"
                 radius: dp(20)
                 backgroundColor: "transparent"
                 borderColor: "green"
                 borderWidth: 2
                 onClicked: {
                     navigationStack.popAllExceptFirstAndPush(productComp)
                 }
             }
             Component{
                 id: productComp
                 ProductPage{ }
             }
         }
         AppCard{
             width: parent.width
             paper.radius: dp(10)
             topMargin: contentPadding
             leftMargin: contentPadding
             rightMargin: contentPadding
             bottomMargin: contentPadding
             header: SimpleRow{
                 text: "Câu chuyện của tôi"
                 detailText: "Lương y Nguyễn Văn Chí"
                 style: StyleSimpleRow{
                     backgroundColor: "transparent"
                     detailTextColor: "darkgreen"
                     textColor: "limegreen"
                     selectedBackgroundColor: "limegreen"
                 }
                 onSelected: {
                     navigationStack.popAllExceptFirstAndPush(authorPage)
                 }
             }
             media: AppImage{
                 width: parent.width
                 fillMode: Image.PreserveAspectFit
                 source: "https://lovehands.vn/wp-content/uploads/2021/06/luong-y-nguyen-van-chi.jpg"
             }

             content: Item{
                 width: parent.width
                 height: childrenRect.height
                 Column{
                     width: parent.width
                     AppText{
                         text: "Hơn 10 năm nghiên cứu Y học cổ truyền chữa bệnh"
                         color: "darkgreen"
                         font.bold: true
                         width: parent.width
                         padding: dp(15)
                     }
                     AppText{
                         text: "Y học cổ truyền đã xuất hiện từ rất lâu trước khi nền y học phương tây xuất hiện.\
 Dựa trên Âm dương – Ngũ hành và khả năng hiểu biết, sử dụng các nguồn dược liệu, thảo dược phong phú trong vùng\
 nhiệt đới đã tạo nên một nền y học cổ truyền lâu đời tại Việt Nam."
                         color: "black"
                         width: parent.width
                         leftPadding: dp(10)
                         rightPadding: dp(10)
                     }
                 }
             }
             actions: AppButton{
                 width: parent.width
                 text: "Lương y Nguyễn Văn Chí"
                 textColor: "green"
                 backgroundColorPressed: "green"
                 radius: dp(20)
                 backgroundColor: "transparent"
                 borderColor: "green"
                 borderWidth: 2
                 onClicked: {
                     navigationStack.popAllExceptFirstAndPush(authorPage)
                 }
             }
         }
         Component{
             id: authorPage
             AuthorPage{ }
         }
    }
}
