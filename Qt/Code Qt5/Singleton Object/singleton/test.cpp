#include "test.h"

test::test(QObject *parent) :
    QObject(parent)
{
}

void test::doSomething()
{
   //emit testSignal();
   Tester::Instance()->testSignal();//thêm emit vào trc cx đc. Nó chỉ có tác dụng specific
   //tức ta k thể gọi 1 hàm instance trong static nên ta tạo ra 1 global var để sử dụng như 1 instance
}
//1 hàm static của 1 class k thể gọi đến 1 hàm instance của class đó, vì static tồn tại mà k cần 1 instance. Cx như k
//thể emit an instance signal, slot trong static. Điều này là hiển nhiên. Để làm đc điều đó ta dùng 1 class singleton
//Singleton là 1 class<template> giúp ta tạo ra 1 instance mặc định cho class.
