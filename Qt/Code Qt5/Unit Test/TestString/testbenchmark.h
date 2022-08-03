#include <QtWidgets>
#include <qtest.h>

class TestBenchmark : public QObject
{
    Q_OBJECT
private slots:
    void simple();
    void multiple_data();
    void multiple();
    void series_data();
    void series();
};
