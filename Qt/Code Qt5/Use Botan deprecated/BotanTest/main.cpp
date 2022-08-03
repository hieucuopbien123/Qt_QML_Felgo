#include <QtCore/QCoreApplication>
#include "botanwrapper.h"
#include <QFile>

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    BotanWrapper cWrapper;

    cWrapper.setPassword("!@#$%^&*()_kjnklawh!@ucoi9293");
    cWrapper.setSalt("#$%^&!*@y9sg08dfsdfs");
    //salt là giá trị thêm vào Password để phức tạp hóa giá trị lưu trữ Password, tăng cường tính bảo mật, độ an toàn
    QString cEnc = cWrapper.Encrypt("This is my secret :)");

    qDebug() << cEnc;
    qDebug() << cWrapper.Decrypt(cEnc);
    //encode để chuyển đổi sang định dạng khác giúp cho văn bản phù hợp với nh hệ thống khác nhau,decode sau khi encode thì sẽ
    //quay lại format ban đầu, cách encode là công khai. encrypt là dùng 1 thuật toán cipher để mã hóa giúp bảo mật dữ liệu và
    //chỉ có thể decrypt bằng 1 khóa đặc biệt

    QString encodedStr = cWrapper.Encode("Hello my friend!");
    qDebug() << encodedStr;
    qDebug() << cWrapper.Decode(encodedStr);

    qDebug() << cWrapper.EncryptFile("B:\\Qt\\newGeneration\\Botan Test\\build-BotanTest-Desktop_Qt_5_15_2_MinGW_64_bit-Debug\\OriginalFile.txt",
                                     "B:\\Qt\\newGeneration\\Botan Test\\build-BotanTest-Desktop_Qt_5_15_2_MinGW_64_bit-Debug\\EncyptedFile.txt");
    qDebug() << cWrapper.DecryptFile("B:\\Qt\\newGeneration\\Botan Test\\build-BotanTest-Desktop_Qt_5_15_2_MinGW_64_bit-Debug\\EncyptedFile.txt",
                                     "B:\\Qt\\newGeneration\\Botan Test\\build-BotanTest-Desktop_Qt_5_15_2_MinGW_64_bit-Debug\\DecryptedFile.txt");
    //nó sẽ tự tạo file nếu k có, nó cân hết Unicode, phải dùng đường dẫn tuyệt đối mới đc


    return a.exec();
}
