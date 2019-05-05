#ifndef CLIENTHANDLER_H
#define CLIENTHANDLER_H

#include <QObject>
#include "client.h"
#include "groupsmodel.h"

class ClientHandler : public QObject
{
    Q_OBJECT
    Q_PROPERTY(bool currentStatus READ getStatus NOTIFY statusChanged)

public:
    explicit ClientHandler(QObject *parent = nullptr);
    bool getStatus();
    void requestUserGroups(GroupsModel *groupsModel);

signals:
    void statusChanged(QString newStatus);
    void receivedError(QString err);
    void receivedMessage(QString msg);

public slots:
    void setStatus(bool newStatus);
    void receivedSomething(QString msg);
    int checkForCommand(QString msg);
    int processCommand(QString command);
    void gotError(QAbstractSocket::SocketError err);
    void sendMessage(QString msg);
    void connectToServer();
    void disconnectFromServer();

private:
    Client *client;
    GroupsModel *groupsModel_;
};

#endif // CLIENTHANDLER_H
