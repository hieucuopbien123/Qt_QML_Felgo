#include "libdll.h"

Libdll::Libdll()
{
}

void Libdll::Test()
{
    qDebug() << "Hello from our DLL";
    //quy trình tạo thì ez,ta cứ chọn lib cần tạo là ok xong nó tự tạo marco hay biến trong pro phù hợp,ta chỉ cần tạo lệnh
}
