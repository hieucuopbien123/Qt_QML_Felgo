#include <testbenchmark.h>
#include <QDebug>

void TestBenchmark::simple()
{
    QString str1 = QLatin1String("This is a test string");
    QString str2 = QLatin1String("This is a test string");


    QCOMPARE(str1.localeAwareCompare(str2), 0);//hàm của QString ss theo locale manner
    qDebug() << str1.localeAwareCompare(str2) << "\n";

    QBENCHMARK {
        str1.localeAwareCompare(str2);
    }
    QSKIP("test skip this");
    //QSKIP trong 1 hàm sẽ tránh vc kiểm tra hàm đó. Thg dùng khi chưa viết xong, or biết trc hàm sẽ fail, or phiên bản k hỗ trợ
    //QtTest sẽ chỉ kiểm tra các hàm có các marco qt thôi, ví dụ hàm multiple_data bên dưới nó k kiểm tra. Nó test các marco đó.
}

//dùng benchmark cx chỉ cho ta thời gian, chi phí chạy hàm mà nó đo. Nhét hàm cần đo vào bench mark.
//tức là nếu nhét hàm đó vào 1 vòng lặp iteration thì mỗi lần chạy sẽ tốn bao nhiêu giây.
//Lúc chạy máy sẽ thực hiện hàm rất nhiều lần r cho kêt quả pass hay k chứ kp là thực hiện 1 lần đâu.
//Còn QBENCHMARK thì thực hiện chắc hàng ngàn lần để đo. Khi vào benchmark, clock coi như dừng lại và hàm lặp lại lt.

void TestBenchmark::multiple_data()
{
    QTest::addColumn<bool>("useLocaleCompare");
    QTest::newRow("locale aware compare") << true;
    QTest::newRow("standard compare") << false;
}

void TestBenchmark::multiple()
{
    QFETCH(bool, useLocaleCompare);
    QString str1 = QLatin1String("This is a test string");
    QString str2 = QLatin1String("This is a test string");

    int result;
    if (useLocaleCompare) {
        QBENCHMARK {
            result = str1.localeAwareCompare(str2);
        }
    } else {
        QBENCHMARK {
            result = (str1 == str2);
        }
    }
    Q_UNUSED(result);
}

void TestBenchmark::series_data()
{
    QTest::addColumn<bool>("useLocaleCompare");
    QTest::addColumn<int>("stringSize");

    for (int i = 1; i < 10000; i += 2000) {
        QByteArray size = QByteArray::number(i);
        QTest::newRow(("locale aware compare--" + size).constData()) << true << i;
        QTest::newRow(("standard compare--" + size).constData()) << false << i;
        //chuyển từ QByteArray sang const char* vì newRow nhận const char
    }
}

void TestBenchmark::series()
{
    QFETCH(bool, useLocaleCompare);
    QFETCH(int, stringSize);

    QString str1 = QString().fill('A', stringSize);
    QString str2 = QString().fill('A', stringSize);
    int result;
    if (useLocaleCompare) {
        QBENCHMARK {
            result = str1.localeAwareCompare(str2);
        }
    } else {
        QBENCHMARK {
            result = (str1 == str2);
        }
    }
    Q_UNUSED(result);
}

//QTEST_MAIN(TestBenchmark)
