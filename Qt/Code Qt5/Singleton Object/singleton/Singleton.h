#ifndef SINGLETON_H
#define SINGLETON_H

#include <assert.h>//để dùng đc assert

//chỉ cần giữ class này, dùng file h này ở bất cứ project nào là dùng đc singleton pattern

template <class T>
class Singleton
{
public:
    static T* Instance()
    {
        if(!m_Instance) m_Instance = new T;
        assert(m_Instance != NULL);
        return m_Instance;
        //cái này là khởi tạo cấp vùng nhớ cho biến static và lấy nó ra. Nếu ta dùng instance nhiều lần thì đương
        //nhiên là nó chỉ tạo ở lần đầu tiên còn các lần sau hàm chỉ có công dụng lấy biến static ra dùng.
        //=>như v ta có thể dùng 1 biến static của class T truy xuất thông qua hàm instance=> tức vai trò class này
        //là giúp ta có 1 instance duy nhất của bất cứ class nào khác->dùng bất kỳ hàm nào của class đó như là static
        //cái này k phải để lạm dụng và vc tạo biến class T vẫn cần thiết. Vd ta cần 1 hàm bên trong class T k là static
        //nhưng lại muốn dùng thì có thể lợi dụng class này
    }

protected:
    Singleton();
    ~Singleton();
private:
    Singleton(Singleton const&);//copy constructor để truyền đc copy vào hàm
    Singleton& operator=(Singleton const&);
    static T* m_Instance;
};

template <class T> T* Singleton<T>::m_Instance=NULL;
//gán giá trị cho biến static là null->là giá trị ban đầu của biến khi dùng class
//gọi vào hàm ::Instance thực ra là lấy cái biến static m_Instance này

#endif // SINGLETON_H
