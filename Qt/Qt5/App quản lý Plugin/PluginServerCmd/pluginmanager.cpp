#include "pluginmanager.h"

PluginManager::PluginManager(QObject *parent) : QObject(parent)
{
    path = QDir::currentPath() + "/Plugins";
    if(!QDir(path).exists())
    {
        qDebug() << "Plugins directory is not exist!";
    }
}

void PluginManager::install(QString filename)
{
    emit pluginResponse("Start installing " + filename);
    QString pluginPath = path + "/" + filename;
    QPluginLoader pluginLoader(pluginPath);
    qDebug() << pluginLoader.fileName();
    QObject* object = pluginLoader.instance();
    if(object)
    {
        InterfaceForPlugin* interface = qobject_cast<InterfaceForPlugin*>(object);
        //static_cast buoc phải kế thừa mới cast đc còn qobject_cast chỉ cần bản chất nó có là cái kia là đc(=dynamic_cast)
        PluginItem* item = new PluginItem(&pluginLoader,interface);
        qDebug() << item->loader->fileName();
        listPluginItem << item;
        qDebug() << listPluginItem.at(0)->loader->fileName();
        emit pluginResponse("Install succesfully!\n\r");
    }
    else
    {
        qDebug() << "Cannot load plugin! ", pluginLoader.errorString();
        emit pluginResponse("Install fail!");
    }
}

void PluginManager::runAll()
{
    if(listPluginItem.count() == 0)
    {
        emit pluginResponse("There is no plugin installed!\n\r");
        return;
    }
    foreach(PluginItem* item,listPluginItem)
    {
        InterfaceForPlugin* interface = item->interface;
//        interface->functOfPlugin("Hello From Plugin");//chạy cái widgets này sẽ bị lỗi kết thúc Ct luôn. Cụ thể nó kết thúc
        //cái event của thread task, k bắt signal/slot nx mà ta k hiểu vì sao.
        emit pluginResponse("A plugin is running\n\r");
    }
}

void PluginManager::list()
{
    if(listPluginItem.count() == 0)
    {
        emit pluginResponse("There is no plugin installed!\n\r");
        return;
    }
    //k hiểu sao hàm loader nó k còn lưu file name nx nên k hđ. Nhưng do file name nó là 1 thuộc tính của item plugin
    //nên có thể lưu như thuộc tính lấy ra như này
    foreach(PluginItem* item,listPluginItem)
    {
        emit pluginResponse(item->getName() + "\n\r");
    }
}

void PluginManager::uninstall(QString filename)
{
    foreach(PluginItem* item,listPluginItem)
    {
        QString linkToFile = item->filename.split('/').last();
        if(linkToFile == filename)
        {
            item->~PluginItem();
            listPluginItem.removeOne(item);
            emit pluginResponse("Removed successfully!\n\r");
            return;
            //trong qPluginLoader có hàm load và unload quyết định có load cái file plugin.dll k. Khi dùng instance sẽ tự
            //gọi load, khi terminate sẽ tự gọi unload, nhưng trong các TH muốn load in advance thì cứ dùng
        }
    }
    emit pluginResponse("That plugin doesn't exist!\n\r");
}
