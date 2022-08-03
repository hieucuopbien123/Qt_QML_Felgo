#include "dialog.h"
#include "ui_dialog.h"

Dialog::Dialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::Dialog)
{
    ui->setupUi(this);
}

Dialog::~Dialog()
{
    delete ui;
}

void Dialog::on_TestPlugin_clicked()
{
    //MĐ: ta ấn vào nút là load 1 phát tất cả plugin luôn. Tất cả plugins dll ta gom vào 1 folder r chạy từng file load
    //chứ test 1 cái plugin thì ez quá, dùng mỗi pluginLoader là xong
    QDir pluginsDir(QDir::currentPath() + "/plugins");

    foreach(QFileInfo fileInfo, pluginsDir.entryInfoList(QDir::Files))
    //còn nhớ là cái entry thì nó lấy cả folder . và .. nên cần lọc chỉ lấy file QDir::Files
    //entryInfoList trả về QFileInfo còn entryList trả về QString
    {
        loadPlugin(pluginsDir.absolutePath() + "/" + fileInfo.fileName());
        //k lấy đc relative ở 1 file nào mà chỉ lấy đc absolute vì relative là ./ luôn r nhưng tùy vào nơi nào gọi khác nhau
        //có relative khác nhau nên-> luôn dùng absolute nếu lấy đg dẫn file nào dùng làm gì khi biết tên file
        //ta cần truyền link file còn cái kia chỉ return cái tên file chứ kp link file
    }
}

void Dialog::loadPlugin(const QString& pluginFile)
{
    QPluginLoader pluginLoader(pluginFile);
    qDebug() << pluginFile;
    QObject* objectPlugin = pluginLoader.instance();

    //instance của QPluginLoader sẽ trả ra QObject* là cái khởi nguồn của plugin, vì mọi plugin đều phải kế thừa từ QObject
    //nếu đó kp là plugin or bị lỗi sẽ return nullptr
    if(objectPlugin)
    {
        //để dùng:tạo QPluginLoader từ link file dll->lấy instance của nó->cast sang interface và dùng đc cac hàm trong interface
        InterfaceForPlugin* plugin = qobject_cast<InterfaceForPlugin*>(objectPlugin);
        plugin->functOfPlugin("test Plugin");
    }
    else
    {
        qDebug() << "Not a plugin: " << pluginLoader.errorString();//lấy lỗi
    }
}
