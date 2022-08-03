#include <QCoreApplication>
#include <QDebug>
#include <array>
#include "laptop.h"

void getLaptop(laptop laptop)
{
    laptop.name += "1";
    qInfo() << "Object name of var copy: " << laptop.objectName();
    return;
//    ta đã tạo copy constructor nên biến này cục bộ hủy ở đây sẽ thấy rõ với tên khác là đã copy
//    nó copy biến laptop theo các thứ ta gán trong hàm copy-constructor chứ k gọi vào constructor default của laptop
}

void test()
{
    laptop laptop1(nullptr, "My laptop");
    laptop1.setObjectName("Test");
    getLaptop(laptop1);
}

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    int end = 0;
    if(end) qFatal("End program");

    std::array<int,4> testArray = {1, 3, 2, 4};
    for(size_t i = 0; i < testArray.size(); i++)
        qInfo() << "array[" << i << "]= " << testArray.at(i) << "\n";
    //các biến cục bộ khai báo ở đây sẽ k bị xóa cho đến khi kết thúc ct vì hàm exec()

    test();

    return a.exec();
}
