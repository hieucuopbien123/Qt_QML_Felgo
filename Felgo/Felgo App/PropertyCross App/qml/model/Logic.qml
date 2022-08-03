import QtQuick 2.0
import Felgo 3.0

Item {
    signal useLocation()
    signal searchListings(string searchText, bool addToRecents)//khởi tạo string, bool như C++
    signal showRecentSearches()
    signal loadNextPage()
    signal toggleFavourite(var listingData)//or khởi tạo var như js đều đc
}
