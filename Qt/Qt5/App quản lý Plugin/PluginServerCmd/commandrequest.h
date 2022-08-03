#ifndef COMMANDREQUEST_H
#define COMMANDREQUEST_H

#include <QString>
#include <QList>
#include <QObject>

class CommandRequest
{
public:
    CommandRequest();

public:
    QString command;
    QList<QString> args;

    void getRequest(QString commandBuffer);
};

//Q_DECLARE_METATYPE(CommandRequest)

#endif // COMMANDREQUEST_H
