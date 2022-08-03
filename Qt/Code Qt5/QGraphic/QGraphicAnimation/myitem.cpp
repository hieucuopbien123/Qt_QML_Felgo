#include "myitem.h"
#include <QDebug>

MyItem::MyItem()
{
    //QRandomGenerator có 3 hàm static là securelySeeded expensive, nên dùng global hay nhất, k nên dùng system cho vc trả
    //ra dữ liệu số lượng lớn. Hàm seed của class này nhận vào 1 seed là đối số để sinh ra số ngẫu nhiên, seed khác nhau thì
    //sẽ sinh ra 1 chuỗi số khác nhau.Nếu 2 biến cùng seed gọi generate thì sẽ cho ra cùng chuỗi giá trị=>Đó chính là lý do hàm
    //srand() nhận đối số time(NULL) là vì hàm đó nhận seed và truyền vào time biến thiên liên tục sẽ sinh số khác nhau mỗi lần
    //Hàm generate sẽ sinh số quint32, nếu dùng generate64 se sinh quint64 hay gọi generate của QRandomGenerator64 tương tự.
    //(static lấy max, min nx, set bounded cho nó min âm thì có thể ra âm dương, còn generate%-1 sẽ ra chỉ âm)
    //ôi ngáo vãi: muốn giá trị âm thì %2000-1000 là có từ -1000 đến 1000
    //Q_ASSERT(bool) kiểm tra điều kiện bên trong sai thì gọi qFatal(""); sẽ dừng Ct.
    Q_ASSERT(1);
    if(0) { qFatal("Hàm test k chạy"); }
    Q_ASSERT_X(1,"noi co loi","loi gi");

    //Phiên bản qt mới k dùng qsrand(seed) rồi qrand() nx mà dùng QRandomGenerator. Nó cx truyền vào seed qua hàm seed() or
    //dùng ở hàm khởi tạo. Nếu k truyền thì seed lấy mặc định và các giá trị đó sẽ là như nhau. Cùng seed thì kết quả là 1.
    //Dùng QRandomGenerator::global() thì mỗi lần dùng sẽ tự thay seed khác nhau nên generate ra số khác. Có thể dùng nó luôn
    //or dùng nó làm seed thay thế cho time(NULL) cx ok. Tương tự system() và securelySeed()
    ranEngine = new QRandomGenerator(QRandomGenerator::global()->generate());
    ranEngine->bounded(-1000,1000);//thế là cả âm cả dương ngẫu nhiên, seed lấy cái trên cho nó đổi mỗi lần compile

    //1 item xuất hiện r di chuyển thì cần: tốc độ, hướng, vị trí xuất hiện
        setRotation(QRandomGenerator::global()->generate()%360);

    int startX = QRandomGenerator::global()->generate()%200 - 150;
    int startY =  QRandomGenerator::global()->generate()%200 + -150;
    setPos(startX,startY);

    speed = 5;
}

QRectF MyItem::boundingRect() const
{
    return QRectF(0,0,20,30);
}

void MyItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    QRectF rect = boundingRect();

    QPen pen(Qt::black);
    QBrush brush(Qt::green);

    if(!collidingItems().isEmpty())
    {
        brush.setColor(Qt::red);
        DoCollision();
    }

    painter->setBrush(brush);
    painter->setPen(pen);
    painter->drawRect(rect);
    //       painter->drawText(rect.x(),rect.y(),"Hello");
}
//hàm collidingItems(item)của scene sẽ trả về danh sách các item of scene và chạm vơi item đó bao gồm cả item và cả shape,thực
//chất nó kiểm tra bằng hàm collidesWithItem của QGraphicsItem phát ra khi có bất cứ va chạm giữa item vs item or scene.Cả
//scene và item đều có collidingItems. collidesWithItem của item kiểm tra sự va chạm của item này vs 1 item specific khác.
//collidingItems của scene/item kiểm tra mọi sự va chạm của 1 item bất kỳ trong scene/vs item này

//thực chất: Khi ta thêm 1 item vào scene thì là ta đang thêm vào scene 1 hệ trục tọa độ canvas. Mỗi 1 item có 1 cái canvas độc
//lập và k ảnh huong j tới hệ trục tọa độ của scene trong view. Ban đầu cái canvas này mặc định là trùng vs hệ tọa độ của scene
//trong view. Cái boudingRect là tọa độ của item trong cái canvas đó, item luôn bị giới hạn trong cái boundingRect và k thể ra
//ngoài, để di chuyển item thì chỉ có cách gọi các hàm transformation di chuyển cái canvas đi chỗ khác vd setPos hay setRotation
//đều là hàm di chuyển canvas. Mỗi item đều có canvas cx như mỗi painter đều có canvas v nhưng ở đây ta chỉ cần dùng canvas của
//item k dùng của painter.Do đó bounding rect k đổi và ta gọi painter draw vào cái boundingRect nhưng vật lại di chuyển là do
//canvas chứa cái boundingrect đó đôi. setPos là set tâm của canvas sang vị trí nào của parent mẹ là scene, còn bounding rect là
//vị trí vẽ vật trong cái canvas(tọa độ của vật trong canvas(boundingrect) luôn là số cố định)
//Hàm mapToParent thực chất nhận tọa độ so với con là tọa độ trong canvas chứa bounding rect trả về tọa độ trong parent là
//scene chứa item đó=>chuẩn.
//Vd: item ở trong scene. Lúc đầu đáng lẽ canvas của item trùng với scene(trùng gốc (0,0)). Lúc khởi tạo ta setPos(10,10)
//chẳng hạn thì canvas có tâm(0,0) trùng tâm(0,0) bh nó lại trùng vs điểm(10,10) tức là lệch xuống dưới bên phải. Giả sử item
//có boundingRect là (-200,-200,100,100) thì đó là tọa độ trong canvas, tọa độ của nó trong scene ta nhìn thấy sẽ là (-190,-190)
//giả sử ta muốn vật di chuyển sang phải 5 pixel liên tiếp thì ta phải di chuyển canvas sang phải 5 pixel. Dùng setPos di canvas
//nhưng nó nhạn tọa độ trong scene nên phải mapToParent lấy tọa độ trong canvas item chuyển sang tọa độ của scene->truyền vào
//setPos(mapToParent(5,0))-> lúc này (5,0) là tọa độ so với gốc (0,0) của canvas tương ứng với (15,10) của scene tức là
//setPos(15,10)-> di chuyển tâm canvas từ (10,10) thành (15,10)-> boundingRect vẫn cố định trong canvas nhưng so với scene nó
//bị đổi thành(-185,-190) và đó là bản chất cách tạo animation

//hàm advance thực chất là hàm giúp ta tạo animation: khi gọi slot advance của scene thì nó sẽ gọi đến ham advance của từng
//item một 2 lần với 2 gđ. Gđ 1 nó truyền vào phase bằng 0 báo rằng scene cbi đổi và gđ 2 là phase == 1 báo rằng nó co thể move.
//Hàm này của scene giúp cho vc connect dễ hơn vì ta chỉ cần connect signal cho 1 hàm advance của scene sẽ gọi advance
//của tát cả item chứ kp connnect từng item. Do có 2 phase mà ta chỉ cần thực hiện 1 lần nên thêm if(!phase) return;
//Nếu ta muốn tạo animation mà k dùng advance thì cx đc. Vì item k phải QObject nên viết hàm di chuyển trong class cua nó k đc
//nên ta buộc tạo trong cửa sổ->1 list chứa item-> connect r cho nó move là xong. Nhưng ta nên dùng advance cho chuẩn.

void MyItem::advance(int phase)
{
    if(phase == 0) { return; }
    setPos(mapToParent(speed,0));
}

void MyItem::DoCollision()
{
    //khi có va chạm xảy ra cần set góc nó quay ngc lại và vị trí của nó bị va chạm thành k bị va chạm
    setRotation(rotation() + 180 + ranEngine->generate()%10);
    //giả sử k có setPos ở đây, mà chỉ có setRotation thì vật sẽ quay lại nhưng vị trí nó bị nhảy 1 tí mỗi lần là do kết quả
    //của vc xoay. Chung 1 gốc và bị xoay tưởng tượng sẽ thấy-> do đó ta k muốn vật xoay như v mà tiếp tục cái vị trí cũ=> tức
    //là tọa độ bị lệch nhau 1 khoảng đúng bằng kích thước của vật khi va vào tường bên phải và tường bên trái(TH vật đi sang
    //ngang 2 bên) nhưng cũng cần cho nó đi 1 đoạn bởi vì nếu  y nguyên như vị trí cũ tức là
    //nó đang va chạm tường lại va chạm tường tiếp

    QPointF point = mapToParent(-boundingRect().width()+2,-boundingRect().height());
    //xoay r ms xét vị trí nhé=> cần biến sang dỉnh đối diện
    if(scene()->sceneRect().contains(point))
    setPos(point);//chấp nhận chịu TH đặc biệt thì nó sẽ nhảy 1 đoạn là lấy VT cũ chứ k set
    //vc kiểm soát va chạm ta phải quét hết mọi TH-> vì nó va chạm vs tường sẽ có 3 TH xảy ra thẳng/ nghiêng từ dưới/nghiêng
    //từ trên và còn 4 TH 4 bức tường phải xem giống hay khác. Ta chỉ cần set góc nghiêng mới và vị trí mới cho object để nó
    //bắt đầu di chuyển.
    //Vấn đề là giả sử ta cho đi sang ngang va với tường thì tọa độ của nó phải đổi sang là cái đỉnh phía đối diện, xét trong
    //cái canvas thì sẽ như bên trên nhưng TH nó va vào tường bên trái từ dưới lên thì dùng v sẽ toang vì ra ngoài cái scene.
    //Do v ta vẫn chưa xử lý đc TH đó, nếu dùng sin cos thì ra mnr
    //Xác định các thứ cần làm cả về thực tế lẫn cơ chế r xác định vị trí đặt ham và viết hàm
}

//Thực tế: scene có nhiều item ở vị trí random-> sau mỗi 100ms các item di chuyển loạn xạ-> nếu va vào thành bình sẽ chuyển màu
//đỏ và bật ngc lại, va vào các item khác cũng tương tự
//Cơ chế: scene thêm các item vào-> set vị trí và boudingrect cho item->connect timer vs advance và ham advance phải cho item
//di chuyển về phía trc vì rotation set ngẫu nhiên r->gọi advance thì hàm vẽ cũng đc gọi vẽ item-> vẽ item vào boundingRect->
//kiểm tra va chạm trong hàm vẽ: va chạm xảy ra thì set brush màu đỏ-> nếu có va chạm thì cho nó rotation ngc lại
//và set vị trí cho nó lùi về 1 bước
