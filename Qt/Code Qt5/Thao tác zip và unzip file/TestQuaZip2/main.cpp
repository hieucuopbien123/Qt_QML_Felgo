#include <QCoreApplication>
#include <QDebug>
#include "JlCompress.h"

//compressFile, compressFiles, compressDir, extractFile, extractFiles, extractDir, getFileList

void compressFiles(QString finalZipFile, QStringList fileToCompress)
{
    //khi dùng thư viện bên thứ ba thường có kiểu init với kiểm tra ntn
    //nén single với compressFile, nén 1 list file với compressFiles
    if(JlCompress::compressFiles(finalZipFile, fileToCompress))
    {
        qDebug() << "Created " << finalZipFile;
    }
    else
    {
        qDebug() << "Could not compress " << fileToCompress;
    }
}

void decompressFiles(QString zipFileToBeExtracted, QStringList fileNameToBeExtracted, QString folderToSave)
{
    //tức là 1 cái file.zip nén nhiều file thì ta muốn extract file nào bên trong ra
    QStringList nameList = JlCompress::extractFiles(zipFileToBeExtracted,fileNameToBeExtracted,folderToSave);
    //trả ra tên các file giải nén thành công
    foreach(QString name, nameList)
    {
        qDebug() << "Extracted: " << name;
    }
}

void compressDir(QString finalZipFile, QString dirToBeCompressed)
{
    if(JlCompress::compressDir(finalZipFile, dirToBeCompressed))
    {
        qDebug() << "Compressed " << finalZipFile;
    }
    else
    {
        qDebug() << "Could not compress " << finalZipFile;
    }
}

void decompressDir(QString zipFileToBeExtracted, QString ExtractedDir)
{
    QStringList itemList = JlCompress::extractDir(zipFileToBeExtracted,ExtractedDir);
    foreach(QString item, itemList)
    {
        qDebug() << "Extracted " << item;
    }
}

void listContent(QString zipFile)
{
    QFile file(zipFile);//k đọc hay ghi thì k cần mở, chỉ cần 1 biến lưu file để kiểm tra sự tồn tại
    if(!file.exists())
    {
        qDebug() << "File " << zipFile << " is not exist!";
    }
    QStringList list = JlCompress::getFileList(zipFile);
    foreach(QString item, list)
    {
        qDebug() << item;
    }
}

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

//    compressFiles("Compressed/new.zip",QStringList() << "Original/new.txt");
//    decompressFiles("Compressed/new.zip",QStringList() << "new.txt", "NewDir");
//    compressDir("Compressed/Compressed Dir/dir.zip","Original");
//    decompressDir("Compressed/Compressed Dir/dir.zip","NewDir2");
    listContent("Compressed/Compressed Dir/dir.zip");

    return a.exec();
}
