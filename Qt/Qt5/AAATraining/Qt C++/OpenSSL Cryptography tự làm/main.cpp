#include <QCoreApplication>
#include "crypto.h"
#include <string.h>
#include "QFile"
#include "QDir"

QByteArray getPrivateKey()
{
    QFile file;
    file.setFileName("../Draft/Key/private.pem");
    if(!file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        qDebug() << "Cannot open file to read" << file.errorString();
    }
    QTextStream stream(&file);
    QByteArray byteArray = stream.readAll().toUtf8();
    file.close();
    return byteArray;
}

QByteArray getPublicKey()
{
    QFile file("../Draft/Key/public.pem");
    if(!file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        qDebug() << "Cannot open file to read";
    }
    QTextStream stream(&file);
    QByteArray byteArray = stream.readAll().toUtf8();
    file.close();
    return byteArray;
}

void testRSA()
{
    QByteArray publicKey = getPublicKey();
    QByteArray privateKey = getPrivateKey();

    QByteArray message = "This is message to test RSA";
    Cipher wrapper;
    QByteArray ecrypted = wrapper.encryptRSA(message, publicKey);
    QByteArray derypted = wrapper.decryptRSA(ecrypted, privateKey);
    qDebug() << ecrypted.toBase64();
    qDebug() << derypted;
}

void testAES()
{
    QByteArray message = "This is message to test AES";
    Cipher wrapper;
    QByteArray pass = "1801";

    QByteArray encrypted = wrapper.encryptAES(message, pass);
    QByteArray decrypted = wrapper.decryptAES(encrypted, pass);

    qDebug() << encrypted.toBase64();
    qDebug() << decrypted;
}

int main(int argc, char* argv[])
{
    QCoreApplication app(argc, argv);
    testRSA();
    testAES();

    return app.exec();
}
