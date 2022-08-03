import QtQuick 2.0
import Felgo 3.0
import "./pages"
import "./model"

Item {
    Logic{
        id: logic
    }

    Model{
        id: model
        dispatcher: logic
    }

    MainPage{
    }
}
