#include <testgui.h>

void TestGui::testGui()
{
    QLineEdit lineEdit;

    QTest::keyClicks(&lineEdit, "hello world");

    QCOMPARE(lineEdit.text(), QString("hello world"));

    QFETCH(QTestEventList, events);
    QFETCH(QString, expected);
    events.simulate(&lineEdit);

    QCOMPARE(lineEdit.text(), expected);
}

void TestGui::testGui_data()
{
    QTest::addColumn<QTestEventList>("events");
    QTest::addColumn<QString>("expected");

    QTestEventList list1;
    list1.addKeyClick('a');
    QTest::newRow("char") << list1 << "a";

    QTestEventList list2;
    list2.addKeyClick('a');
    list2.addKeyClick(Qt::Key_Backspace);
    QTest::newRow("there and back again") << list2 << "";
}

//Cách simulate GUI Event: hàm keyclicks sẽ mô phỏng hoạt động của bàn phím trên widget
//->ví dụ: QTest::keyClicks(myWidget, "hello world"); sẽ chọn myWidget, sau đó gõ bàn phím cụm hello world
//->Ở TH này nếu myWidget là 1 line edit thì sẽ như kiểu viết gõ hello world vào line edit

//Cách lưu lại các sự kiện để bấm liên tiếp hoặc thực hiện 1 chuỗi sự kiện để test nh hàm khác nhau
//QTestEventList chuyên lưu các event vào 1 list
//addColumn tạo title, newRow lưu giá trị

//QTEST_MAIN(TestGui)
