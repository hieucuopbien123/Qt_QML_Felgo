#ifndef CRYPTO_H
#define CRYPTO_H

#include <QObject>
#include <QDebug>
#include <openssl/rsa.h>
#include <openssl/engine.h>
#include <openssl/pem.h>
#include <openssl/conf.h>
#include <openssl/evp.h>
#include <openssl/err.h>
#include <openssl/aes.h>
#include <openssl/rand.h>

#define PADDING RSA_PKCS1_PADDING
#define KEYSIZE 32
#define IVSIZE 32
#define SALTSIZE 8

class Cipher: public QObject
{
    Q_OBJECT
public:
    explicit Cipher(QObject* parent = 0);
    ~Cipher();

    QByteArray encryptRSA(QByteArray message, QByteArray publicKey);
    RSA* getRSAPublicKey(QByteArray publicKey);
    QByteArray decryptRSA(QByteArray message, QByteArray privateKey);
    RSA* getRSAPrivateKey(QByteArray privateKey);

    QByteArray encryptAES(QByteArray message, QByteArray pass);
    QByteArray getSalt(int size);
    QByteArray decryptAES(QByteArray encrypted, QByteArray pass);

private:
    void initialize();
    void finalize();

};

#endif
