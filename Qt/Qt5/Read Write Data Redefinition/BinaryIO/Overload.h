#ifndef OVERLOAD_H
#define OVERLOAD_H

#include <QtCore>
#include "myclass.h"

QDataStream &operator>>(QDataStream& in, MyClass& person);
QDataStream &operator<<(QDataStream& out,const MyClass& person);

QDataStream &operator<<(QDataStream& out,const MyClass& person)
{
    out << person.age << person.name;
    return out;
}

QDataStream &operator>>(QDataStream& in, MyClass& person)
{
    person = MyClass();//thừa thãi
    in >> person.age >> person.name;
    return in;
}

#endif // OVERLOAD_H
