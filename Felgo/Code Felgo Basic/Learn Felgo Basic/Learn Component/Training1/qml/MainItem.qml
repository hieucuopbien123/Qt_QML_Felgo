import QtQuick 2.0
import Felgo 3.0
import "./logic"
import "./model"
import "./pages"

Item {
    Logic{
        id: logic
    }
    Model{
        dispatcher: logic
        id: model
    }

    MainPage{}
}
