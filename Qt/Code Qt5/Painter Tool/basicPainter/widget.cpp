#include "widget.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
}

Widget::~Widget()
{
    delete ui;
}

void Widget::paintEvent(QPaintEvent *event)
{
    //cần gì tạo con trỏ, gọi thì tạo biến ra thì xóa là đc r, ta k cần connect signal slot gì nên k cần pointer.vẽ tĩnh
    //painter k nhận đối số or QPaintDevice là class đc kế thừa bởi các class có thể bị vẽ lên bởi QPainter-> rất nh
    //truyền vào thứ mà ta muốn vẽ lên, hiển nhiên là cửa sổ this r

    //QPainter lo vc vẽ lên màn hình
    //QPen lo nét bút vẽ line
    //QBrush lo nét bút tô 1 vùng

    QPainter painter(this);

    QPen blackPen(Qt::black);
    blackPen.setWidth(6);
    QPen redPen;
    redPen.setColor(Qt::red);
    redPen.setWidth(2);

    QBrush brush(Qt::blue,Qt::DiagCrossPattern);
    QBrush brushForPoly;
    brushForPoly.setColor(Qt::yellow);
    brushForPoly.setStyle(Qt::SolidPattern);

    QPoint point1;
    point1.setX(10);
    point1.setY(10);
    QPoint point2(100,100);

    QRect rect(100,10,100,100);//2 cách khởi tạo 2 điểm or 1 điểm 1 QSize

    //vẽ hình học cơ bản
    painter.setPen(redPen);
    painter.drawLine(point1,point2);

    painter.setPen(blackPen);
    painter.drawPoint(point1);
    painter.drawPoint(point2);

    painter.drawRect(rect);

    painter.drawEllipse(rect);

    painter.fillRect(rect.x()+100,rect.y(),rect.width(),rect.height(),brush);

    //vẽ polygon bất kỳ
    QPolygon poly;
    poly << QPoint(150,150);
    poly << QPoint(150,200);
    poly << QPoint(200,150);
    poly << QPoint(200,200);

    QPen bluePen(Qt::blue);
    bluePen.setWidth(2);
    bluePen.setJoinStyle(Qt::MiterJoin);//or Qt::RoundJoin/BevelJoi
    bluePen.setStyle(Qt::DotLine);
    bluePen.setCapStyle(Qt::RoundCap);//Qt::SquareCap Qt::FlatCap

    //để dùng đc brush cho poly ta phải fill vào cái poly nhưng poly k phải rect mà là các đg path
    QPainterPath path;
    path.addPolygon(poly);

    painter.fillPath(path,brushForPoly);
    painter.drawPolygon(poly);//vẽ các điểm theo thứ tự và tự nối 2 điểm cuối

    //QGradient
    QLinearGradient lGrad(250,150,350,250);//grad cx chỉ là 1 cái brush chuyển màu(k set mặc định là đen trắng)
    //nó tạo ra một bức màn trên màn hình của chúng ta với hai điểm thì dải màu sẽ chuyển tiếp giữa 2 điểm đó, màu nào là do ta
    //tự set. Hàm setColorAt sẽ tạo ra tỉ lệ chuyển màu giữa 2 điểm, tỉ lệ chỉ đcd truyền từ 0->1
    //=>ví dụ ta truyền vào 2 điểm nằm ngang thì dải màu sẽ đổi từ từ theo chiều ngang
    //=>các điểm nằm ngoài 2 điểm này sẽ mang màu của điểm ngoài cùng đậm nhất 0.0 và 1.0, các cái khác cơ chế là tương tự
    lGrad.setColorAt(0.0,Qt::white);
    lGrad.setColorAt(0.2,Qt::green);
    lGrad.setColorAt(1.0,Qt::black);
    QRectF rectLGrad(240,140,100,100);//QRectF là floating point của QRect
    painter.fillRect(rectLGrad,lGrad);//thay cho brush trong các hàm vẽ

    QRadialGradient rGrad(QPoint(50,150),50);
    rGrad.setColorAt(0.3,Qt::white);
    rGrad.setColorAt(0.5,Qt::green);
    rGrad.setColorAt(1.0,Qt::black);
    QRectF rectRGrad(0,100,100,100);//QRectF là floating point của QRect
    painter.fillRect(rectRGrad,rGrad);//thay cho brush trong các hàm vẽ

    QConicalGradient cGrad(QPoint(360,60),0);
    cGrad.setColorAt(0.0,Qt::white);
    cGrad.setColorAt(0.2,Qt::green);
    cGrad.setColorAt(1.0,Qt::black);
    QRectF rectCGrad(310,10,100,100);
    painter.fillRect(rectCGrad,cGrad);

    //Text
    painter.drawText(450,50,"Hello World!");//ta có thể draw vào vị trí cụ thể nào or xác định phạm vi giới hạn

    QRect rectText(400,150,200,100);
    painter.drawRect(rectText);
    painter.drawText(rectText,Qt::AlignLeft,"Left");//vẽ text trong 1 phạm vi rect điều chỉnh
    painter.drawText(rectText,Qt::AlignCenter,"Center");
    painter.drawText(rectText,Qt::AlignRight | Qt::AlignCenter,"Right");
    //phạm vi rect nhỏ hơn thì text sẽ tự động bị cắt

    QTextDocument doc;
    QRect rectTextDocument(0,0,500,200);//đây là cái khung phạm vi hiển thị text
    painter.translate(500,50);//offset bắt đầu viết từ đâu, nếu nằm ngoài khung bên trên sẽ không hiện
    doc.setTextWidth(10);//set chiều dài của dòng, nếu nhỏ hơn text thì text sẽ bị xuống dòng hàng dọc ví dụ chữ hello lớn hơn
    //10 pixels nên bị xuống dòng. Nếu kích thước 0 pixel thì hiển thị như bth
    doc.setHtml("<b><u>Hello</u></b> <br><br> <font face='Arial'>World</font>");//điểm lợi QTextDocument là stylize text đc HTML
    doc.drawContents(&painter,rectTextDocument);//hàm vẽ k là của painter mà của QTextDocument-> gọi vẽ bằng QPainter, set chỉ
    //hiện trong khung, nếu biến rect là QRect() (default) sẽ in full text
    //->setHtml+drawContents là xong

    //transformation
    QRect rectTransformation(200,350,100,100);
    blackPen.setWidth(1);
    painter.setPen(blackPen);
    painter.resetTransform();
    painter.drawRect(rectTransformation);
    //hàm translate bản chất là sẽ lùi màn hình vẽ đi một khoảng bao nhiêu so với gốc (0,0)-> gốc đó bị đổi khi gọi và các lệnh
    //về sau cx bị ảnh hưởng-> các lệnh làm transformation sẽ làm thay đổi cả cái canvas(là cái màn hình ta render ra) thông qua
    //vc thay đổi từ cái gốc tọa độ (0,0), nó làm canvas thay đổi vĩnh viễn và các hàm sau nếu vẫn dùng QPainter đo thì sẽ theo
    //cái cavas đó, nên muốn dùng bth thì phải resetTransformation đi or dùng painter khác
    //VD: translate(1,2); thì tọa độ (10,10) sẽ thành tọa độ (11,12) so với cái màn hình ban đầu

    //=>ở painter khác view, khi transformation cái painter thì canvas đổi là đổi màn hình sẽ vẽ chứ các hình đã vẽ luôn cố
    //định. View thì xoay luôn màn hình hiển thị(Các đối tượng đã vẽ là biến toàn cục đã bị xóa nhưng vẫn còn)
    painter.rotate(10);//cái kim rotate xoay xuôi kim đồng hồ là góc dương
    painter.setPen(bluePen);
    painter.drawRect(rectTransformation);

    painter.setPen(redPen);
    painter.scale(0.7,0.7);//từ gốc, co nhỏ lại 0.7 so với gốc theo tỉ lệ. Gốc trên cùng bên trái
    painter.drawRect(rectTransformation);

    painter.resetTransform();
    painter.shear(0.1,0.1);//làm hai trục tọa độ nghiêng đi và dịch vị trí-> vẽ hình vuông thành hình thoi
    painter.drawRect(rectTransformation);
}
