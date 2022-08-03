#include "commandrequest.h"
#include <QDebug>

CommandRequest::CommandRequest()
{
    command = "";
}

void CommandRequest::getRequest(QString commandBuffer)
{
    args = commandBuffer.split(' ',Qt::SkipEmptyParts);
    command = args[0];
    args.removeAt(0);
}
