#include <QCoreApplication>
#include <QList>
#include <QDebug>
#include <QLinkedList>
#include <QMap>
#include <QVector>

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    //QList bth
    QList<int> testIntList;
    testIntList << 4 << 4 << 5 << 2 << 1;
    testIntList.append(100);
    testIntList.insert(1,50);
    testIntList.removeAll(4);
    testIntList.removeOne(100);
    testIntList.replace(1,40);
//    qDebug() << testIntList.at(0);
//    testIntList.clear();

    qSort(testIntList.begin()+1,testIntList.end()-1);
    std::sort(testIntList.begin()-1,testIntList.end()+1,std::less<int>());//bắt buộc truyền iterator
    qSort(testIntList);

    QList<int>::const_iterator Iter=qFind(testIntList.begin(),testIntList.end(),40);
    //trả về con trỏ vào 1 list xuất hiện vị trí đầu tiên cái giá trị ta tìm, có thể dùng ::iterator tức QMutableListIterator
    //thực chất QList<int>::iterator và QListIterator<int> nó có Vt giống nhưng thực ra khác nhau, k dùng đc hàm của nhau
    //Iter=testIntList.begin()+1

    //QListIterator chỉ cho ta duyệt qua list và xem chứ k cho ta thay đổi->muốn đổi QMutableListIterator
    QListIterator<int> iteratorIntList(testIntList);
    iteratorIntList.toBack();
    while(iteratorIntList.hasPrevious())
    {
        qDebug() << iteratorIntList.previous();
        //hàm này vừa trả về giá trị đằng trc vừa lùi con trỏ lại
    }
    qDebug() << "The first value is" << iteratorIntList.peekNext();//lấy mà k dịch con trỏ
    QMutableListIterator<int> iteratorMutableIntList(testIntList);
    iteratorMutableIntList.remove();
    //QMutableListIterator cx có các hàm như QListIterator nhưng có thêm các hàm xóa, thao tác này nọ. QList cx khá đủ hết r

    //QLinkedList: linked list là 1 danh sách như các list bth chỉ có điều các ô nhớ trong list k liên tiếp nhau,1 ô sẽ lưu int
    //và cả tham chiếu đến địa chỉ ô tiếp theo,còn lại giống QList.Linked list có kích thước linh hoạt, dễ dàng thêm và xóa hơn
    //Còn array/list thì truy xuất phần tử dễ hơn, bộ nhớ ít hơn.
    //Vì linked list mỗi ô lưu thêm tham chiếu. Khi xóa 1 phần tử trong mảng thì xóa xong phải lùi toàn bộ ô nhớ, còn linked
    //list thay đổi mỗi tham chiếu của 2 ô kề. Khi lấy 1 phần tử linked list buộc duyệt toàn bộ, array cần index là xong.
    QLinkedList<QString> list;//k có at
    list << "one" << "two" << "three";//cần xóa thêm bớt với kích thước linh hoạt thì dùng linked list

    //QMap
    QMap<int,QString> map;
    map.insert(1,"Nguyen");
    map[3]="Thu";
    map.insertMulti(3,"Hieu");//hàm này cổ r, ng ta dùng QMultiMap để lưu map có các GT trùng
    foreach(int i,map.keys())
    {
        qDebug() << i << " " << map[i];
    }

    QMapIterator<int,QString> mapIterator(map);
    while(mapIterator.hasNext())
    {
        mapIterator.next();
        qDebug() << mapIterator.key() << " " << mapIterator.value();
    }//QMapIterator bỏ qua insertMulti của QMap

    //QHash giống y hệt QMap, nhưng nó lợi hơn ở chỗ: tìm kiếm phần tử nhanh hơn;Iterate loạn trong hash chứ k theo key như map

    //QStringList
    QStringList strList;
    strList.append("Nguyen");
    strList.append("Thu");
    strList.replace(1,"Hieu");
    QString strFromStrList=strList.join(" ");
    qDebug() << strFromStrList;

    QVector<QString> vect(5);
    qCopy(strList.begin(),strList.end(),vect.begin()+1);//giống std::copy,vect có ptu 0 là ""

    qFill(vect.begin()+3,vect.end(),"test");//std::fill
    foreach(QString test,vect)
    {
        qDebug() << test;
    }





    return a.exec();
}
