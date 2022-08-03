import QtQuick 2.0
import Felgo 3.0

Item {
    signal queryProduct()
    signal queryBlog(int code)
    signal querySearch(string searchString)
    signal toggleFavourite(string titleParam, string contentParam)
}
