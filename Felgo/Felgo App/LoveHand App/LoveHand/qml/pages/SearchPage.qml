import QtQuick 2.0
import Felgo 3.0

FlickablePage {
    id: root
    //flickable.contentHeight: searchResultsList.height
    //cái này gây lỗi. Chú ý khi dùng FlickablePage thì page nó tự flick nhìn hết các con bên trong mà k cần
    //set như này, Tự dưng như này nó có lỗi là: Nếu bên trong là 1 item bth thì k sao nhưng nếu là các kiểu list
    //app, page thì sẽ khiến cho các thứ đó full màn hình chứ k còn dưới navbar nx vì nó xđ 1 Page chứa 1 page khác
    //thì nằm dưới Page đó và chiếm toàn bộ. Tức là k ổn nếu là 1 kiểu dạng như Page lại lồng vào 1 page
    scrollIndicator.visible: true
    rightBarItem: NavigationBarItem {
      Row {
        property real backButtonWidth: dp(Theme.navigationBar.height)//kích thước menubutton là hình vuông trùng luôn
        height: dp(Theme.navigationBar.height)
        width: root.width - backButtonWidth
        anchors.right: parent.right

        SearchBar {
          id: searchBar
          inputBackgroundColor: Theme.backgroundColor
          barBackgroundColor: "transparent"
          anchors.verticalCenter: parent.verticalCenter
          enabled: !dataModel.loading
          showClearButton: true
          iconRightPadding: dp(contentPadding/2)//chính là chỉnh clearButton

          width: textField.displayText != "" ? ((!indicator.visible) ? parent.width - clearButton.width : parent.width - clearButton.width - indicator.width) : parent.width
          Behavior on width {NumberAnimation{duration: 150; easing.type: Easing.InOutQuad}}

          textField.onEditingFinished: {
              if(textField.displayText != "")
                logic.querySearch(textField.text)
          }
        }

        AppButton {
          id: clearButton
          flat: true
          text: "Tìm kiếm"
          anchors.verticalCenter: parent.verticalCenter
          horizontalMargin: 0
          textColor: "white"
          textColorPressed: Qt.darker(Theme.textColor, 1.2)
          textSize: sp(14)

          opacity: searchBar.textField.displayText != ""//visible
          //opacity min là 1 max là 0 cho như v để tiện vì có thể set true(1) là hiện, false(0) là ẩn
          //opacity kp là mờ đi và thành trống đâu mà là kiểu visible ấy ẩn đi luôn, opacity là visible có mức độ thôi
          Behavior on opacity {NumberAnimation{duration: 150}}

          onClicked: {
            searchBar.textField.focus = false
            logic.querySearch(textField.text)
              //chỉ cần focus=false thì text bar cx tự gọi editing finish
          }
        }
        ActivityIndicatorBarItem{
            id: indicator
            visible: dataModel.loading
        }
      }
    }

    AppListView {
      id: searchResultsList
      anchors.fill: parent

      emptyView.children: [
        Column {
          anchors.centerIn: parent
          width: searchResultsList.width * 0.75
          spacing: dp(10)

          AppText {
            width: parent.width

            fontSize: 18
            font.bold: true
            horizontalAlignment: Text.AlignHCenter
            text: qsTr("Tìm kiếm từ khóa cho các bài đăng")
          }

          AppText {
            width: parent.width

            color: Theme.secondaryTextColor
            fontSize: 12
            horizontalAlignment: Text.AlignHCenter
            text: dataModel.loading ? qsTr("Đang tìm kiếm...") : qsTr("Hiện chưa có bài đăng nào phù hợp kết quả tìm kiếm")
            wrapMode: Text.WordWrap
          }
        }
      ]

      model: JsonListModel{
          id: modelSearch
          source: dataModel.searchedBlogs
          fields: ["title","content"]
      }

      delegate: SimpleRow {
        detailText: item.title
        item: modelSearch.get(index)
        style: StyleSimpleRow{
            detailTextColor: "black"
            selectedTextColor: "green"
        }
        onSelected: {
            console.log("Item: " + item.content)
            navigationStack.popAllExceptFirstAndPush(blogContentComponent,{titleParam: item.title, contentParam: item.content})
        }
      }
      Component{
          id: blogContentComponent
          BlogContentPage{}
      }
    }
}
