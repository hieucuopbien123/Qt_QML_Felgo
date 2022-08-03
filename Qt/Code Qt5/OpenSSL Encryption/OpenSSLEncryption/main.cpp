#include <QCoreApplication>
#include "cipher.h"

QByteArray getPublicKey()
{
    QByteArray testPublicKey;

    testPublicKey.append("-----BEGIN PUBLIC KEY-----\n");
    testPublicKey.append("MIIBIjANBgkqhkiG9w0BAQEFAAOCAQ8AMIIBCgKCAQEAnqXlIdgpIW6o05RJkxpc\n");
    testPublicKey.append("YpHPQVNpwD/BBpUpWylj72gKSDYU+bfBYFrKNEFfaXmwGhp5lCwaktcYaEl4jL0a\n");
    testPublicKey.append("jd8sZrIY+AnQ7iKLSpz4kjz5DOwtWIhrd1HW9iaJqzOO8ooEmtuih4g/V/NZEI7S\n");
    testPublicKey.append("1BOEDKWUaA2sq5DsXMYA9VJ+tQwauHDmLn8WAf9bZLbGL1ydSbI5bT555sLnmb1D\n");
    testPublicKey.append("noCOxO/I+yDx0ETnv+e0A4WQLvFxh/DwQiqV8TDU0Ve1EX7pjQ0e89rtBxyfmyeS\n");
    testPublicKey.append("DXnlyRNKSEq7XEVb2fz8NEHuMzwDQKGEHagpCL4i7NkZwYMvyTPooQSk5ekE2/M2\n");
    testPublicKey.append("gwIDAQAB\n");
    testPublicKey.append("-----END PUBLIC KEY-----");

    return testPublicKey;
}

QByteArray getPrivateKey()
{
    QByteArray testPrivateKey;

    testPrivateKey.append("-----BEGIN RSA PRIVATE KEY-----\n");
    testPrivateKey.append("MIIEowIBAAKCAQEAnqXlIdgpIW6o05RJkxpcYpHPQVNpwD/BBpUpWylj72gKSDYU\n");
    testPrivateKey.append("+bfBYFrKNEFfaXmwGhp5lCwaktcYaEl4jL0ajd8sZrIY+AnQ7iKLSpz4kjz5DOwt\n");
    testPrivateKey.append("WIhrd1HW9iaJqzOO8ooEmtuih4g/V/NZEI7S1BOEDKWUaA2sq5DsXMYA9VJ+tQwa\n");
    testPrivateKey.append("uHDmLn8WAf9bZLbGL1ydSbI5bT555sLnmb1DnoCOxO/I+yDx0ETnv+e0A4WQLvFx\n");
    testPrivateKey.append("h/DwQiqV8TDU0Ve1EX7pjQ0e89rtBxyfmyeSDXnlyRNKSEq7XEVb2fz8NEHuMzwD\n");
    testPrivateKey.append("QKGEHagpCL4i7NkZwYMvyTPooQSk5ekE2/M2gwIDAQABAoIBAHKs369THIf6ATbO\n");
    testPrivateKey.append("3U/johvt4a4KqUo5y0EC2N34UTBgN+5yiT7oQHNxrO+QwXLwbwavVGpyZtL1f8MC\n");
    testPrivateKey.append("OI0is+sRAntJCRthnRBFEAJi7JpoUG2y2iRAl82r7oIG4URLBGz0rtdxI05sgb0F\n");
    testPrivateKey.append("Pb/mPSbm5HBvz5JXMBTjsLZuuYqZb2Foyqh8V8hOTFBlM+IE4V1m+3S3tIxhTLQO\n");
    testPrivateKey.append("jLzN3t8l0+dBZaJrvYodCrXxJtAU2iLcmlNS2v1k5fy1kNbUzb9dBOgAmhDKrpq5\n");
    testPrivateKey.append("tXkzxvMrAmE3vlHn/N/FMvdjlbnOYq9Gi/YW72SwW/QEWfyRArVys0MlfZJk58Uk\n");
    testPrivateKey.append("wwgMfiECgYEAzw9+/bvwMKk7wOyvm3Wt/rwhqUBjEIwfa+yirws8HbQhLNuqUQUt\n");
    testPrivateKey.append("tlt8Dy0y+MMPZWEqEgZHKsqgyXR8/GO72pq8CaaEM1d/Iv1LajjL4gOQmeNRjJYf\n");
    testPrivateKey.append("K+hX7/9tEuuArqFBdgJGPZ8BcaCbj/HCL8RhkVysqd5KiVHhBHuoSwcCgYEAxCUg\n");
    testPrivateKey.append("96Bx7BOB83M/QU+Axg3p3dEMA1pxV2ZXHyO6bsGk3KRPD7UB/wz4SfoTO7AyfybN\n");
    testPrivateKey.append("B7O9zAlyprcMAmIJCIxy6j/Hnhv/csQwnwGvGoEBdHhCci6PAE/h0fyjFCnBuKIe\n");
    testPrivateKey.append("i/b8amw8UXwQQSMbPbzyBClBOgF3G4uptf2YjaUCgYEAvv3ZMmy/sfL4Rg1MMgaL\n");
    testPrivateKey.append("dxPLrNXSSvolJaTBrtqbGf8ENt9sK42uS635MfqMML+kHOxSJQwbaxI623gSra/F\n");
    testPrivateKey.append("IHBoEDLDcKQ9hmXDwXggQBrvr7LpjtcOa67GJn8h+ji2mt3ths+0QLTBXTE7LLxg\n");
    testPrivateKey.append("VTU8lhu4vHtpn16iQ0NYydMCgYArryk8fVth/KZAljZMUWyYr5iacmh+hrIfiQd2\n");
    testPrivateKey.append("Q/rNmAsjqOSC1wluyHCz6SJHdOKKNxYK1Rk8TA5g2vutvC/O25jsWvAWYp3t7Yv2\n");
    testPrivateKey.append("neVlvb2ZNv91drEanK/qmJ2pa/NdL54mBggJm7mDXGIyX6M9iMtN6fJA/PqOA/j0\n");
    testPrivateKey.append("M1q6kQKBgFrA3KS3YSL4rCnOU1WVpf1Reaz6abzgNMn5yufqoHUfO3fTnlHgLegh\n");
    testPrivateKey.append("dPXD3IdqzQe09sFfRSPPzRIUPL1ilziqNgPvgAmDoAN/UuVuvag3tB9b4UUPMgwv\n");
    testPrivateKey.append("eQO9pJJ1bO26g1nFDX3mIkYSrgZNxbmwL0A4c4nCqiS2ehzeAbm5\n");
    testPrivateKey.append("-----END RSA PRIVATE KEY-----");

    return testPrivateKey;
}

bool readFile(QString filename, QByteArray &data)
{
    QFile f(filename);

    if(!f.open(QFile::ReadOnly))
    {
        qCritical() << "Could not open " << filename;
        return false;
    }

    data = f.readAll();
    f.close();
    return true;
}

bool writeFile(QString filename, QByteArray &data)
{
    QFile f(filename);
    if(!f.open(QFile::WriteOnly))
    {
        qCritical() << "Could not open " << filename;
        return false;
    }

    f.write(data);
    f.close();

    return true;
}

void testRSA()
{
    qDebug() << "Loading keys..";
    QByteArray testPrivateKey = getPrivateKey();
    QByteArray testPublicKey = getPublicKey();
    qDebug() << testPublicKey.size();

    Cipher cWrapper;
    RSA* publickey = cWrapper.getPublicKey(testPublicKey);
    RSA* privatekey = cWrapper.getPrivateKey(testPrivateKey);

    QByteArray plain = "The man in black fled into the desert and the gunslinger followed...";

    QByteArray encrypted = cWrapper.encryptRSA(publickey,plain);
    QByteArray decrypted = cWrapper.decryptRSA(privatekey,encrypted);


    qDebug() << plain;
    qDebug() << encrypted.toBase64();
    qDebug() << decrypted;

    cWrapper.freeRSAKey(publickey);
    cWrapper.freeRSAKey(privatekey);
}

void testAES()
{
    qDebug() << "Testing AES...";

    Cipher cWrapper;
    QString passphrase = "password";
    QByteArray plain = "The man in black fled into the desert and the gunslinger followed (with aes)123456...";

    //cái password cần được mã hóa bằng RSA
    QByteArray encrypted = cWrapper.encryptAES(passphrase.toLatin1(),plain);
    QByteArray decrypted = cWrapper.decryptAES(passphrase.toLatin1(),encrypted);

    qDebug() << plain;
    qDebug() << encrypted.toBase64();
    qDebug() << decrypted;
}

//A sẽ dùng encryptCombined tạo ra 1 file chứa những thứ cần gửi cho B. B dùng decryptCombined giải mã cái file đó
bool encryptCombined()
{
    Cipher cWrapper;

    //Encrypt the AES key
    QByteArray key = getPublicKey();
    RSA* publickey = cWrapper.getPublicKey(key);

    QByteArray passphrase = cWrapper.randomBytes(8).toBase64();
    QByteArray encryptedKey = cWrapper.encryptRSA(publickey,passphrase);

    qDebug() << "Encrypted AES key = " << encryptedKey;

    //Encrypt the data
    QByteArray plain = "Hello world this is plain text!";
    QByteArray encrypted = cWrapper.encryptAES(passphrase,plain);

    QString filename = "test.enc";
    QFile f(filename);
    if(!f.open(QFile::WriteOnly))
    {
        qCritical() << "Could not open " << filename;
        return false;
    }

    qDebug() << "Encrypted Key Len: " << encryptedKey.length();

    QByteArray encryptedData;
    encryptedData.append(encryptedKey);
    encryptedData.append(encrypted);
    f.write(encryptedData);
    f.close();

    qDebug() << "Encryption Finished!";

    cWrapper.freeRSAKey(publickey);

    return true;
}

bool decryptCombined()
{
    Cipher cWrapper;
    QByteArray data;

    if(!readFile("test.enc", data))
    {
        qCritical() << "Could not open test.enc";
        return false;
    }

    //Load the encrypted key from the file
    QByteArray header("Salted__");
    int pos = data.indexOf(header);
    if(pos == -1)
    {
        qCritical() << "Could not find the beginning of the encrypted file!";
        return false;
    }

    qDebug() << header << " found at " << pos;

    QByteArray encryptedKey = data.mid(0,256);
    QByteArray encrypted = data.mid(256);

    //Decrypt the AES key
    QByteArray key = getPrivateKey();
    RSA* privateKey = cWrapper.getPrivateKey(key);
    QByteArray passphrase = cWrapper.decryptRSA(privateKey,encryptedKey);
    cWrapper.freeRSAKey(privateKey);

    qDebug() << "Passphrase = " << passphrase;

    //Decrypt the data
    QByteArray plain = cWrapper.decryptAES(passphrase, encrypted);

    writeFile("test.txt", plain);

    qDebug() << "Finished Decrypting!";
    return true;
}

void encryptCommandLine()
{
    QString passphrase = "passphrase";
    QByteArray plain = "Hello from the openssl command line!";
    writeFile("file.txt", plain);

    qDebug() << "Encrypting on the command line";
    system("openssl aes-256-cbc -salt -md sha1 -in file.txt -out file.enc -pass pass:passphrase");

    qDebug() << "Decrypting with application";

    Cipher cWrapper;
    QByteArray encrypted;
    if(!readFile("file.enc", encrypted))
    {
        qCritical() << "Could not open file.enc";
        return;
    }

    QByteArray decrypted = cWrapper.decryptAES(passphrase.toLatin1(),encrypted);

    if(!writeFile("file_decrypted.txt", decrypted))
    {
        qCritical() << "Could not write file_decrypted.txt";
        return;
    }

    qDebug() << "Finished command line test";
}

void decryptCommandLine()
{
    qDebug() << "Encrypting...";

    Cipher cWrapper;
    QString passphrase = "password";
    QByteArray password = passphrase.toLatin1();
    QByteArray plain = "Hello from our application!";

    QByteArray encrypted = cWrapper.encryptAES(password,plain);

    if(!writeFile("file.enc", encrypted))
    {
        qCritical() << "Could not open file.enc";
        return;
    }

    qDebug() << "Decrypting...";
    system("openssl aes-256-cbc -d -salt -md sha1 -in file.enc -out file2.txt -pass pass:password");
    //dùng cmd phải cd đến thư mục exe, còn lệnh system dùng tự nhiên, k bị hỏng biến global
    //không được dùng + passphrase mà phải viết rõ ra-> chú ý dùng commandline phải nv, nếu k nó tự thêm \0\n\r ở cuối

    qDebug() << "Complete";

}

void testCombined()
{
    if(encryptCombined()) decryptCombined();
}

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

//    testRSA();
    testAES();
//    testCombined();

//    encryptCommandLine();
//    decryptCommandLine();

    return a.exec();
}
