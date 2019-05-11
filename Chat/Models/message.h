#ifndef MESSAGE_H
#define MESSAGE_H

#include <QString>

class Message
{
public:
    Message() {}

    QString author;
    QString group_id;
    QString content;
    QString date;
};

#endif // MESSAGE_H
