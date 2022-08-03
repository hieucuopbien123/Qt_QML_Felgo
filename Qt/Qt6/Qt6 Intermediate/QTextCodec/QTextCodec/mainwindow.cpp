#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QTextCodec>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    QByteArray exampleText = "Hello World!!!";
    QString encodedBase64 = exampleText.toBase64(QByteArray::Base64Encoding);
    QByteArray decodedBase64 = QByteArray::fromBase64(encodedBase64.toLatin1());
    ui->textEdit->append("Encoded base 64: " + encodedBase64 + "\n");
    ui->textEdit->append("Decoded base 64: " + decodedBase64 + "\n");

    QString htmlString="Amazonベーシック ハイスピードHDMIケーブル 2.0m (タイプAオス- タイプAオス、イーサネット、3D、オーディオリターン対応)";
    //đây là 1 dòng chữ đã decode r chứ kp rơi vào TH 1 dòng đã encode kb phải decode ra sao. Chứ kbh có chuyển gặp chữ
    //unicode mà bảo hãy decode nó đi. Đã decode r thì decode cái gì nx. Có chữ nhật nên k dùng UTF-8
    QTextCodec* codec = QTextCodec::codecForLocale();//Fit the current area
    qDebug() << codec->name();//System
    codec = QTextCodec::codecForName("Shift-JIS");
    if(codec == nullptr)
        qDebug() << "This codec is not exist in your systems";
    QByteArray encodedString = codec->fromUnicode(htmlString);
    ui->textEdit->append("Encoded: " + encodedString + "\n");
    ui->textEdit->append("Decoded: " + codec->toUnicode(encodedString) + "\n");

    //tạo 1 decoder chung
    QTextDecoder *decoder = codec->makeDecoder(QTextCodec::ConvertInvalidToNull);//tương tự có makeEncoder
    QString string = decoder->toUnicode(encodedString);
    ui->textEdit->append("Decoded by QTextDecoder: " + string + "\n");//trả 1 list QByteArray tên codec chứ kp 1 list codec

    QList<QByteArray> check = QTextCodec::availableCodecs();
    ui->textEdit->append("Some supported charset: ");
    for(QByteArray codecName: check)
        ui->textEdit->append(codecName);//tự xuống dòng
}

MainWindow::~MainWindow()
{
    delete ui;
}

