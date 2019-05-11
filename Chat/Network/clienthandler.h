#ifndef CLIENTHANDLER_H
#define CLIENTHANDLER_H

#include <QObject>
#include "client.h"
#include "authenticator.h"
#include "../Models/groupsmodel.h"
#include "../Models/conversationmodel.h"

class ClientHandler : public QObject
{
    Q_OBJECT
    Q_PROPERTY(bool currentStatus READ getStatus NOTIFY statusChanged)

public:
    explicit ClientHandler(Authenticator *authenticator, GroupsModel *groupsModel,
                           ConversationModel *conversationModel, QObject *parent = nullptr);
    bool getStatus();
    void requestUserGroups();
    void requestMessages(unsigned int group_id);

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
    void clearMessages();

private:
    Client *client;
    Authenticator *authenticator_;
    GroupsModel *groupsModel_;
    ConversationModel *conversationModel_;
};

#endif // CLIENTHANDLER_H
