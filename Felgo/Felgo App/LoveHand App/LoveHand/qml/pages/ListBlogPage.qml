import QtQuick 2.0
import Felgo 3.0
import QtQuick.Controls 1.4

//ListPage tự flickable
ListPage {
    title: "Chủ đề bài viết"

    rightBarItem: NavigationBarRow{
        ActivityIndicatorBarItem{
            visible: dataModel.loading
        }
        IconButtonBarItem{
            icon: IconType.heart
            title: "Mục yêu thích"
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

    model:[
        {type: "Kiến thức", text: "Tâm linh", code: 182},
        {type: "Kiến thức", text: "Thiền - Yoga", code: 184},
        {type: "Kiến thức", text: "Học tập", code: 183},
        {type: "Kiến thức", text: "Làm đẹp", code: 179},
        {type: "Kiến thức", text: "Làm giàu", code: 180},
        {type: "Kiến thức", text: "Ẩm thực", code: 181},
        {type: "Kiến thức", text: "Giải trí", code: 185},
        {type: "Phòng - Chữa bệnh", text: "Sơ cứu - Cấp cứu", code: 186},
        {type: "Phòng - Chữa bệnh", text: "Ung thư", code: 190},
        {type: "Phòng - Chữa bệnh", text: "Phòng tránh", code: 141},
        {type: "Phòng - Chữa bệnh", text: "Bệnh người già", code: 188},
        {type: "Phòng - Chữa bệnh", text: "Bệnh phụ nữ", code: 189},
        {type: "Phòng - Chữa bệnh", text: "Bệnh trẻ em", code: 187},
        {type: "Phòng - Chữa bệnh", text: "Bệnh thường gặp", code: 191},
        {type: "Phòng - Chữa bệnh", text: "Bài thuốc nam", code: 193}
    ]
    section.property: "type"
    delegate: SimpleRow{
        showDisclosure: true
        onSelected: {
            logic.queryBlog(item.code)
        }
    }
    Connections{
        target: dataModel
        onFinishBlogGetting:{
//            if(navigationStack.depth == 1)
                navigationStack.push(listBlogContentComponent,{modelParam: model, titleParam: titleParam})
        }
    }
    Component{
        id: listBlogContentComponent
        ListBlogContentPage{}
    }
}
