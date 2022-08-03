#include "widget.h"
#include "ui_widget.h"
#include <QDebug>

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);

    scene = new QGraphicsScene(this);
    ui->graphicsView->setScene(scene);

    ui->graphicsView->setRenderHint(QPainter::Antialiasing);
    //    ui->graphicsView->setSceneRect(-100,-200,300,300);
    scene->setSceneRect(-200,-200,300,300);

    //phân biệt scene rect của view và scene rect của scene: nếu scene rect của view k đc set thì nó lấy scene rect của scene,
    //nếu đc khai báo thì nó tách rời với scenerect của scene và k bh bị ảnh hưởng. Vai trò scenerect của view là xác định dùng
    //thanh scrollbar trong view. còn scenerect của scene lưu thông số về phạm vi rect mà các widget hiển thị. Nếu ta khai báo
    //thì thông số này là cố định, nếu ta k khai báo thì nó sẽ tự động thay đổi theo vc ta move object đi xa cỡ nào.
    //Lưu ý: cái này luôn là hcn; vc xác định cái này thông thường để dùng thanh scrollbar và xác định tọa độ mong muốn chứ k
    //lq j đến các item bên trong. Các item hoàn toàn có thể move ra ngoài đều ok và nếu ta kéo màn hình lớn ra đủ thì vẫn nhìn
    //thấy đc hết.
    //VD: k khai báo screenrect của scene(có thể khai báo screenrect của view) mà ta vẽ lên màn hình các line như bên dưới lấy
    //topLeft của rect mà màn hình chưa co cj thì sẽ k hiện ra gì cả, k vẽ đc line=> là do scenerect lúc này là (0,0,0,0)

    //Về vấn đề tọa độ: tọa độ của view trong widget là tọa độ so với cửa sổ. Khi ta kéo dãn cửa số thì cái view bị dãn theo do
    //ta dùng layout nên tọa độ tự thay đổi. tọa độ của scene trong view chính là cái scenerect chả có gì, còn về mặt hiển
    //thị ra cho ng dùng xem thì (0,0) của scene luôn nằm center của view, Nếu scenerect đc set 1 cách thủ công thì màn hình
    //sẽ bị lệch đi hiển thị sao cho cái scenerect của view có tâm luôn ở tâm view. Còn tọa độ của item khi ta dùng hàm add
    //thì các item đều đã specific cái tọa độ của nó chính là trong hệ tọa độ của scene so vs view chứ chả có khác->thêm 1
    //item vào vị trí nào của rect.

    //Tuy nhiên trong qua trình sử dụng sau khi add vào r thì các item sẽ mang 1 hệ tọa độ ms của chính nó. Với các item mặc
    //định thì cái vị trí xuất hiện đầu tiên trong scene là gốc, gọi là bounding rect. Nó là tọa độ so với trục tọa
    //độ của parent, là hình chữ nhật bao quát toàn bộ hình với góc bên trên trái là tọa độ. Các item ta tự tạo thì ta
    //xác định cái boundingrect theo cái tọa độ ở trong parent chứa nó-> thì cái gốc bounding rect đó là tọa độ của item đó
    //trong canvas. Khi ta dùng hàm x(), y() lấy tọa độ của item thì đó chính là tọa độ của canvas. Nếu k set vị
    //trí cho item của ta thì nó sẽ mặc định ở tâm 0,0 của canvas

    //Bản chất các hàm ánh xạ của item là lấy tọa độ. VD: item->mapToParent(point); thì ở đây xuất hiện 2 đối tượng là point
    //và item. point ở đây là đối tượng con trong cái hệ tọa độ so với cái item ở thời điểm hiện tại.
    //itemMovable là canvas item đó movable

    //Khi kết hợp các hàm transformation: ví dụ hàm setRotation thì thực chất là xoay từ gốc là 0,0, sau đó thì cái
    //tọa độ bounding rect trong canvas vẫn giữ nguyên còn cái canvas bị xoay

    QPen myPen(Qt::red);
    myPen.setWidth(2);

    QLineF topLine(scene->sceneRect().topLeft(),scene->sceneRect().topRight());
    QLineF rightLine(scene->sceneRect().topRight(),scene->sceneRect().bottomRight());
    QLineF leftLine(scene->sceneRect().topLeft(),scene->sceneRect().bottomLeft());
    QLineF bottomLine(scene->sceneRect().bottomLeft(),scene->sceneRect().bottomRight());

    scene->addLine(topLine,myPen);
    scene->addLine(rightLine,myPen);
    scene->addLine(leftLine,myPen);
    scene->addLine(bottomLine,myPen);
    qDebug() << topLine.x1() << topLine.x2();

    int itemCount = 10;
    for(int i = 0; i < itemCount; i++)
    {
        MyItem* item = new MyItem();
        scene->addItem(item);//add nó vào còn vc nó xuất hiện ntn trong hàm khởi tạo ta quyết định.
        qDebug() << item->x() << item->y();
    }

    timer = new QTimer(this);
    connect(timer,SIGNAL(timeout()),scene,SLOT(advance()));
    timer->start(10);
}

Widget::~Widget()
{
    delete ui;
}
