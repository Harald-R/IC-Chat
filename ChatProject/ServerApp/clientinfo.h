#ifndef CLIENTINFO_H
#define CLIENTINFO_H

#include <QList>

class ClientInfo {

public:
    ClientInfo() {}
    ClientInfo(unsigned int userId, QList<unsigned int> groups)
    {
        this->userId = userId;
        this->groups = groups;
    }

    unsigned int userId;
    QList<unsigned int> groups;
};

#endif // CLIENTINFO_H
