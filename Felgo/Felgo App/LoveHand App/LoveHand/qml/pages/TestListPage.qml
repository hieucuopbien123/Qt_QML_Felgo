import QtQuick 2.0
import Felgo 3.0

ListPage {
    model: dataModel.searchedBlogs1
    delegate: SimpleRow{
        detailText: item.title
    }
    emptyText.text: "No data"
}
