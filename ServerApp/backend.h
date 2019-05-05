#ifndef BACKEND_H
#define BACKEND_H

#include <QObject>
#include "server.h"

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
    void clientDisconnectedFromServer();
    void gotNewMesssage(QTcpSocket *clientSocket, QString msg);

private:
    Server *server;
    int userId;
    int checkForCommand(QString msg);
    int processCommand(QTcpSocket *clientSocket, QString command);
};

#endif // BACKEND_H
