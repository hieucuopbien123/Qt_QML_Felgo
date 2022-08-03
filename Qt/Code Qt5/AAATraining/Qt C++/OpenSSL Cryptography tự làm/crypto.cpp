#include "crypto.h"

Cipher::Cipher(QObject* parent): QObject(parent)//khởi tạo ở đây là các biến gán luôn cho cha or khởi tạo trc khi vào hàm
//ví dụ trước khi vào hàm cần chỉnh sửa gì. Gán cha thì tên class như trên, gán  biến thì thay bằng biến vào. Cái này
//gọi là initialisation list-> có thể dùng v để khởi tạo cho biến const cx đc
{
    initialize();
}

Cipher::~Cipher()
{
    finalize();
}

RSA* Cipher::getRSAPublicKey(QByteArray publicKey)
{
    const char* rawKey = publicKey.constData();
    BIO* bioKey = BIO_new_mem_buf((void*)rawKey,-1);
    BIO_set_flags(bioKey,BIO_FLAGS_BASE64_NO_NL);
    RSA* resKey = PEM_read_bio_RSA_PUBKEY(bioKey, NULL, NULL, NULL);
    if(!resKey)
    {
        qDebug() << "Cannot create RSA Public Key" << ERR_error_string(ERR_get_error(), NULL);
    }
    BIO_free(bioKey);
    return resKey;
}

QByteArray Cipher::encryptRSA(QByteArray message, QByteArray publicKey)
{
    RSA* publicRSAKey = getRSAPublicKey(publicKey);
    unsigned char* resString = (unsigned char*)malloc(RSA_size(publicRSAKey));
    int resLength = RSA_public_encrypt(message.size(), (const unsigned char* )message.constData(), resString, publicRSAKey, PADDING);
    //nó chỉ thao tác với const unsigned char* nên phải chuyển, trả ra cx là unsigned phải convert về bth là const char*
    if(resLength == -1)
    {
        qCritical() << "Could not encrypt" << ERR_error_string(ERR_get_error(),NULL);
    }
    QByteArray res = QByteArray((char*)resString, resLength);
    free(resString);
    RSA_free(publicRSAKey);
    return res;
}

RSA* Cipher::getRSAPrivateKey(QByteArray privateKey)
{
    const char* rawKey = privateKey.constData();
    BIO* bioKey = BIO_new_mem_buf((void*)rawKey,-1);
    BIO_set_flags(bioKey,BIO_FLAGS_BASE64_NO_NL);
    RSA* resKey = PEM_read_bio_RSAPrivateKey(bioKey, NULL, NULL, NULL);
    if(!resKey)
    {
        qDebug() << "Cannot create RSA Public Key" << ERR_error_string(ERR_get_error(), NULL);
    }
    BIO_free(bioKey);
    return resKey;
}

QByteArray Cipher::decryptRSA(QByteArray encryptedMess, QByteArray privateKey)
{
    RSA* privateRSAKey = getRSAPrivateKey(privateKey);
    unsigned char* resString = (unsigned char*)malloc(RSA_size(privateRSAKey));
    int resLength = RSA_private_decrypt(encryptedMess.size(), (const unsigned char* )encryptedMess.constData(), resString, privateRSAKey, PADDING);
    if(resLength == -1)
    {
        qCritical() << "Could not decrypt" << ERR_error_string(ERR_get_error(),NULL);
    }
    QByteArray res = QByteArray((char*)resString, resLength);
    //QByteArray kp con trỏ, truyền con trỏ char vào lấy giá trị bth thôi, nên khởi tạo là phải free đi
    free(resString);
    RSA_free(privateRSAKey);
    return res;
}

QByteArray Cipher::encryptAES(QByteArray message, QByteArray pass)
{
    QByteArray salt = getSalt(SALTSIZE);
    unsigned char key[KEYSIZE];
    unsigned char iv[IVSIZE];
    int checkKeySize = EVP_BytesToKey(EVP_aes_256_cbc(), EVP_sha1(), (unsigned char*)salt.constData(),
                                    (const unsigned char*)pass.constData(), pass.length(), 1, key, iv);
    if(checkKeySize != KEYSIZE)
    {
        qDebug() << "Cannot generate key: " << ERR_error_string(ERR_get_error(), NULL);
        return QByteArray();
    }
    EVP_CIPHER_CTX* ctx = EVP_CIPHER_CTX_new();
    if(!EVP_EncryptInit_ex(ctx, EVP_aes_256_cbc(),NULL,key,iv))
    {
        qDebug() << "Cannot init 1: " << ERR_error_string(ERR_get_error(), NULL);
        return QByteArray();
    }
    int len = message.size() + AES_BLOCK_SIZE;
    unsigned char* text = (unsigned char*)malloc(len);
    if(!EVP_EncryptInit_ex(ctx, NULL, NULL, NULL, NULL))
    {
        qDebug() << "Cannot init 2: " << ERR_error_string(ERR_get_error(), NULL);
        return QByteArray();
    }
    if(!EVP_EncryptUpdate(ctx, text, &len, (unsigned char*)message.data(), message.size()))
    {
        qDebug() << "Cannot Update: " << ERR_error_string(ERR_get_error(), NULL);
        return QByteArray();
    }
    int f_len = 0;
    if(!EVP_EncryptFinal(ctx, text + len, &f_len))
    {
        qCritical() << "Cannot finalize encrypting: "  << ERR_error_string(ERR_get_error(), NULL);
        return QByteArray();
    }
    int resSize = f_len + len;
    QByteArray res;
    res.append("Salted__").append(salt).append(QByteArray((char*)text, resSize));
    EVP_CIPHER_CTX_free(ctx);
    return res;
}

QByteArray Cipher::decryptAES(QByteArray encrypted, QByteArray pass)
{
    QByteArray mSalt;
    if(encrypted.startsWith("Salted__"))
    {
        mSalt = encrypted.mid(8,16);
        encrypted = encrypted.mid(16);
    }
    else{
        qDebug() << "Cannot read salt";
        return QByteArray();
    }
    unsigned char key[KEYSIZE];
    unsigned char iv[IVSIZE];
    int checkSize = EVP_BytesToKey(EVP_aes_256_cbc(), EVP_sha1(), (const unsigned char*)mSalt.constData(),
                           (const unsigned char*)pass.constData(), pass.length(), 1, key, iv);
    if(checkSize != KEYSIZE)
    {
        qDebug() << "Cannot get key to decrypt" << ERR_error_string(ERR_get_error(), NULL);
        return QByteArray();
    }
    EVP_CIPHER_CTX* ctx = EVP_CIPHER_CTX_new();
    if(!EVP_DecryptInit_ex(ctx, EVP_aes_256_cbc(), NULL, key, iv))
    {
        qDebug() << "Cannot init to decrypt" << ERR_error_string(ERR_get_error(), NULL);
        return QByteArray();
    }
    int size = AES_BLOCK_SIZE + encrypted.size();//chú ý length khác size
    int len = encrypted.size();
    int p_len = len;
    unsigned char* text = (unsigned char*)malloc(p_len + AES_BLOCK_SIZE);
    if(!EVP_DecryptUpdate(ctx, text, &p_len, (unsigned char*)encrypted.data(), len))
    {
        qDebug() << "Cannot update to decrypt" << ERR_error_string(ERR_get_error(), NULL);
        return QByteArray();
    }
    int f_len = 0;
    if(!EVP_DecryptFinal_ex(ctx, text + p_len, &f_len))
    {
        qCritical() << "EVP_DecryptFinal_ex() failed " <<  ERR_error_string(ERR_get_error(), NULL);
        return QByteArray();
    }
    EVP_CIPHER_CTX_free(ctx);
    QByteArray res((char*)text, p_len + f_len);// chú ý là p_len nó bị đổi thế nào éo biết
    return res;
    //nch là đúng quy y hệt về size, mà chả cần làm lại các hàm này làm gì, chỉ cần thừa hay thiếu 1 tí là kết quả sẽ ảo ngay
}

QByteArray Cipher::getSalt(int size)
{
    unsigned char arr[size];
    RAND_bytes(arr,size);
    QByteArray buffer = QByteArray((char*)(arr), size);
    return buffer;
}

void Cipher::initialize()
{
    ERR_load_crypto_strings();
    OpenSSL_add_all_algorithms();
}

void Cipher::finalize()
{
    EVP_cleanup();
    ERR_free_strings();
}

//Kinh nghiệm khi làm vc với thư viện bên thứ 3-> nó thường thao tác với raw data là (const) unsigned char* nên ta luôn phải
//cast sang nó khi sử dụng. Nhưng ta k nên sử dụng luôn nó mà phải cast sang QByteArray nếu có thể, chỉ khi nào dùng mới
//chuyển sang raw data, dùng song chuyển qua QByteArray ngay vì thao tác với char* rất dễ lỗi. VD hàm getSalt ở trên return
//char* là rất dễ toang=>nên luôn ưu tiên sử dụng kiểu dữ liệu chuẩn của framework
