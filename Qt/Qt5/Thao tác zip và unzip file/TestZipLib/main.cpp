#include <QCoreApplication>

#include <QDebug>
#include "zipreader.h"
#include "zipwriter.h"

//cái này là miêu tả cho hàm gì viết ngay bên trên hàm /** + <enter> ngay lập tức tạo ra mẫu
/**
 * @brief Compression Test
 * @param ZipFile The zip file
 */
void CompressTest(QString ZipFile)
{
    //ZipWriter cZip(ZipFile);
    //cZip.addDirectory("E:/Development/qt114/QtZipTest/Images");
    //cZip.close();

    ZipWriter cZip(ZipFile);
    QString SingleFile = "B:\\Qt\\newGeneration\\TestQuaZip\\build-TestQuaZip2-Desktop_Qt_5_15_2_MinGW_32_bit-Debug\\Original\\sontung.jpg";
    QFile file(SingleFile);
    file.open(QIODevice::ReadOnly);

    cZip.addFile("test.jpg", file.readAll());

    file.close();
    cZip.close();
}
//ZipWriter là cái nén file,truyền file zip sẽ tạo và mode; addDirectory là hàm xây dựng 1 case thư mục bên trong file
//zip->extract nó thì sẽ đc cả 1 cây thư mục chứ k chỉ mỗi file; addFile-> là nén vào cái zip kia file tên là gì, dữ liệu
//là gì

/**
 * @brief Decompression Test
 * @param ZipFile The zip file
 */
void DecompressTest(QString ZipFile)
{
    ZipReader cZip(ZipFile);
    foreach(ZipReader::FileInfo item, cZip.fileInfoList())
    {
        qDebug() << item.filePath;
    }

    //cZip.extractAll("DEST");

    ZipReader::FileInfo finfo = cZip.entryInfoAt(0);
    QFile file("B:\\Qt\\newGeneration\\TestQuaZip\\build-TestQuaZip2-Desktop_Qt_5_15_2_MinGW_32_bit-Debug\\Original\\sontung1.jpg");
    file.open(QIODevice::WriteOnly);

    file.write(cZip.fileData(finfo.filePath));//tạo ra 1 file y hệt file trong file zip->bản chất là nv khi giải nén

    file.close();
    cZip.close();//close zip files
}
//ZipReader là cái giải nén file(thực chất là đọc dữ liêu j từ file zip)
//truyền vào cái cần giải nén; fileInfoList lấy các file trong zip; ZipReader::FileInfo là kiểu
//dữ liệu biểu diễn 1 phần tử của file zip=>filePath của nó lấy full path; extractAll sẽ giải nén tất cả vào thư mục nào;
//entryInfoAt lấy info file vị trí nào khi nó lưu content của zip như 1 mảng; fileData lấy dữ liệu file dưới dạng bytearray(kiểu
//bytearray này có thể lưu cả ảnh,..); truyền vào tên file cần lấy "để giải nén",thực ra chỉ là ghi lại nd ra file mới
//hàm filePath là lấy path của file trong cây thư mục bên trong file zip nhé, fileData sẽ lấy cái path ấy
//như v: 1 là biết đường link trong file zip, 2 là biết vị trí thứ mấy ở cây thư mục bên trong level đầu tiên qua entryInfoList

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    QString ZipFile = "test.zip";
    CompressTest(ZipFile);
    DecompressTest(ZipFile);

    return a.exec();
}
