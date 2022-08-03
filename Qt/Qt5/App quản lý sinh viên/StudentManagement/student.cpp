#include "student.h"

student::student(QObject *parent) : QObject(parent)
{
    name = "";
    age = 15;
    description = "";
    type = "";
    sex = "";
}
