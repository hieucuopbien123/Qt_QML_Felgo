#ifndef STUDENT_H
#define STUDENT_H

#include <QObject>

class student : public QObject
{
    Q_OBJECT
public:
    explicit student(QObject *parent = nullptr);

signals:
    void dataChanged(student* changedStudent);

public:
    QString name;
    unsigned int age;
    QString sex;
    QString type;
    QString description;
};

#endif // STUDENT_H
