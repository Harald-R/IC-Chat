#ifndef BACKEND_H
#define BACKEND_H

#include <QObject>
#include "server.h"
#include "clientinfo.h"

class Backend : public QObject
{
    Q_OBJECT
public:
    explicit Backend(QObject *parent = nullptr);

signals:
    void clientConnected();
    void clientDisconnected();
    void newMessage(QString msg);

public slots:
    QString stopClicked();
    QString startClicked();
    QString testClicked();
    void clientConnectedToServer();
    void clientDisconnectedFromServer(QSslSocket *clientSocket);
    void gotNewMesssage(QSslSocket *clientSocket, QString msg);

private:
    int checkForCommand(QString msg);
    int processCommand(QSslSocket *clientSocket, QString command);
    ClientInfo getClientInfo(unsigned int user_id);

    Server *server;
    QMap<QSslSocket*, ClientInfo> clientInfos_;
};

#endif // BACKEND_H
