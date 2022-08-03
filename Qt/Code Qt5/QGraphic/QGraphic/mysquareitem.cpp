#include "mysquareitem.h"

mySquareItem::mySquareItem()
{
    pressed = false;
    setFlag(ItemIsMovable);//canvas movable đó
}

QRectF mySquareItem::boundingRect() const
{
    return QRectF(0,0,100,100);//bounding rect-phạm vi luôn là hcn dù shape của hình có là gì, đây là phạm vi giới hạn thôi
}

void mySquareItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{//hàm này cx tự động gọi khi thu nhỏ cửa số r mở lên, điều chỉnh kích thước cửa sổ cx gọi, setPos cũng gọi
    QRectF rect = boundingRect();
    QBrush brush(Qt::blue);

    if(pressed)
    {
        brush.setColor(Qt::red);
    }
    else
    {
        brush.setColor(Qt::green);
    }
    painter->fillRect(rect,brush);//có thể setbrush r draw or draw truyền brush đều đc
    painter->drawRoundedRect(rect,50,20,Qt::AbsoluteSize);
}

void mySquareItem::mousePressEvent(QGraphicsSceneMouseEvent *event)
{//QGraphicsSceneMouseEvent chuyên lưu các event của chuột
    pressed = true;
    update();//để đổi màu bút chứ để di chuyển thì cần gì
    QGraphicsItem::mousePressEvent(event);
}

void mySquareItem::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    pressed = false;
    update();
    QGraphicsItem::mouseReleaseEvent(event);
}
//scene sau khi nối với view có thể dùng addItem để vẽ item do ta tự tạo
//luồng: khi tự tạo thì buộc phải làm 2 hàm boundingRect xác định phạm vi của biến hình của ta, nếu ta set cho
//nó là ItemIsMovable thì bounding rect vẫn v(k hiểu nhầm) nhưng in vị trí mới, và hàm paint sẽ quyết định cái hình
//của ta vẽ ntn, nó tự phát bất cứ khi nào hình của ta đc vẽ. Ở đây ta gọi hàm QGraphicsItem::mousePressEvent(event) chỉ là do ta
//k sử dụng biến event nên để hàm mặc định thực hiện nó=> ấn -> gọi update->tự gọi paint vẽ ra-> nhả cx v.->sai
//Khi dùng graphic view khác paint là vẽ, ta dùng add các đối tượng và các đối tượng đó xác định là động chứ kp tĩnh như paint
//Và ta thao tác với các đối tượng tức là dù ta update hay vẽ thêm thì vẫn chỉ hoạt động trong phạm vi đối tượng. Còn paint khi
//ta paint thì cố định, xóa đi và paint lại y hệt chỗ cũ, chứ graphic di chuyển sang vị trí ms khi paint sẽ paint ở vị trí mới.
//Do đó dùng QPainter(k dùng graphic) thì k di chuyển đc cj. Khi ta di chuyển canvas thì nó in sang vị trí ms nhưng cx chỉ là
//do canvas của cái painter đó di chuyển chứ đúng ra là nó vẫn ghi vào cái canvas vị trí đó. Do đo cái Item rect của nó k cố định
//trong view còn rect của draw của painter luôn fix->sai

//qtr là: cái hàm mouseReleaseEvent và hàm mousePressEvent mặc định kp là k làm gì mà nó có khả năng xử lý tương tác cơ bản
//với item. Ta gọi hàm này để duy tri trạng thái tuong tác hiện tại=>lấy canvas hiện tại, lưu canvas item hiện tại khi click
//và nhả. Ví dụ boundingRect là phạm vi giới hạn của hình, nếu ta ấn nút di
//chuyển thì boundingRect thật ra k đổi mà canvas di chuyển khỏi vị trí gốc. Khi ta nhả chuột ra thì rect của vật sẽ lại quay về
//vị trí gốc, nếu update ta sẽ nhìn thấy=>khi đó ta gọi hàm mouseReleaseEvent thì vị trí của vật sẽ vẫn giữ nguyên như v khi nhả
//chuột ra. MousePressEvent cx có vai trò tương tự nhưng ta chưa đc nhìn thấy vì khi di chuyển nó là movable còn khi nhả chuột
//thì gọi mouseReleaseEvent chứ gọi mousePress chưa thấy tác dụng ở đây. MouseDoubleClick thì hàm mặc định cx gọi MousePressEvent
//cx tương tự=> do đó bản chất kp là boundingRect đổi mà đó là 1 cái hàm lấy rect mà. Ta có thể tự đổi trong hàm boundingrect đó

//mặc định ta di chuyển object đc chỉ cần ItemIsMovable bởi vì mouseReleaseEvent và Press nó đc gọi mặc định r, ở đây ta khai báo
//lại nên phải gọi lại hàm mặc định để nó chạy vị trí chuẩn

//thật ra itemIsMovable là move cái item đó và mỗi lần click hay nhả nó sẽ đổi vị trí canvas luôn bằng cách dùng hàm
//mouseReleaseEvent mặc định. Đó là do nó implement mouseReleaseEvent và gọi hàm đó để làm điều đó. Ở đây ta reimplement đó
//để muốn nó làm thêm 1 nv khác. Ta k thể để nó mất tính năng của itemIsMovable nên phải gọi lại mặc định là nv.
