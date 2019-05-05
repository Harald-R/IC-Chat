#include "backend.h"
#include "server.h"
#include "dbmanager.h"
#include <QRegExpValidator>

Backend::Backend(QObject *parent) : QObject(parent)
{
    server = new Server();
    connect(server, &Server::gotNewMesssage, this, &Backend::gotNewMesssage);
    connect(server->tcpServer, &QTcpServer::newConnection, this, &Backend::clientConnectedToServer);
    connect(server, &Server::clientDisconnected, this, &Backend::clientDisconnectedFromServer);
}

QString Backend::startClicked()
{
    if (!server->tcpServer->listen(QHostAddress::Any, 6547))
    {
        return "Error! The port is taken by some other service";
    }
    else
    {
        connect(server->tcpServer, &QTcpServer::newConnection, server, &Server::newConnection);
        return "Server started, port is opened";
    }
}

QString Backend::stopClicked()
{
    if(server->tcpServer->isListening())
    {
        disconnect(server->tcpServer, &QTcpServer::newConnection, server, &Server::newConnection);

        QList<QTcpSocket *> clients = server->getClients();
        for(int i = 0; i < clients.count(); i++)
        {
            //server->sendToClient(clients.at(i), "Connection closed");
            server->sendToClient(clients.at(i), "0");
        }

        server->tcpServer->close();
        return "Server stopped, post is closed";
    }
    else
    {
        return "Error! Server was not running";
    }
}

QString Backend::testClicked()
{
    if(server->tcpServer->isListening())
    {
        return QString("%1 %2")
                .arg("Server is listening, number of connected clients:")
                .arg(QString::number(server->getClients().count()));
    }
    else
    {
        return QString("%1 %2")
                .arg("Server is not listening, number of connected clients:")
                .arg(QString::number(server->getClients().count()));
    }
}

void Backend::clientConnectedToServer()
{
    emit clientConnected();
}

void Backend::clientDisconnectedFromServer()
{
    emit clientDisconnected();
}

void Backend::gotNewMesssage(QTcpSocket *clientSocket, QString msg)
{
    if (checkForCommand(msg)) {
        if (!processCommand(clientSocket, msg)) {
            qDebug() << "Unable to process command: " << msg;
        }
        return;
    }

    emit newMessage(msg);
}

int Backend::checkForCommand(QString msg)
{
    QRegExp regex("SRV:(login|register|get_groups):([^:]*:)*[^:]*");
    QRegExpValidator v(regex, nullptr);
    int pos = 0;

    return v.validate(msg, pos) == QValidator::Acceptable;
}

int Backend::processCommand(QTcpSocket *clientSocket, QString command)
{
    QStringList stringList = command.split(":");
    QStringList::Iterator iter = stringList.begin();
    iter++;

    qDebug() << *iter;
    if (*iter == "login") {
        iter++;
        QString username = *iter;
        iter++;
        QString password = *iter;

        int user_id = DbManager::checkCredentials(username, password);

        // TODO: map of client_socket -> user_id, since there will be multiple users connected
        this->userId = user_id;
        if (this->userId < 0)
            return -1;

        this->server->sendToClient(clientSocket, "SRV:login:success");
        return 1;
    } else if (*iter == "get_groups") {
        // TODO: get user id for specific client
        QList<QPair<QString,QString>> groupsList = DbManager::getUserGroups(this->userId);

        QString reply = "SRV:groups:";
        for (const auto &group : groupsList) {
            QString id = group.first;
            QString name = group.second;
            reply.append(id);
            reply.append(",");
            reply.append(name);
            reply.append(":");
        }

        this->server->sendToClient(clientSocket, reply);
        return 1;
    } else {
        qDebug() << "Unknown command";
    }

    return 0;
}
