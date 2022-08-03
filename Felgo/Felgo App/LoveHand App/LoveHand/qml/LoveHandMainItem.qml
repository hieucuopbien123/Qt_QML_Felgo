import QtQuick 2.0
import Felgo 3.0
import "./pages"
import "./logics"
import "./model"

Item {
    Logic{
        id: logic
    }
    DataModel{
        id: dataModel
        dispatcher: logic
    }
    //như này thì 2 cái id trên sẽ là global để dùng. Chú ý về phạm vi của id. Trong cùng 1 trang thì có thể dùng
    //đc id của nhau và các con của 1 component cũng dùng đc id của sibling. Còn dùng id cha và cha dùng id con đc
    //Nhưng nếu 1 component có con là file khác, xong trong component đó và trong file riêng kia đều có id khác nhau
    //thì id của cha chỉ dùng trong cha, id của file chỉ dùng trong file đó. Vì component là file đó có thể dùng nh nơi
    //mà nên đâu thể dùng đc của nhau và dùng đc id của nhau
    LoveHandMainPage{}
}
