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
        if (processCommand(clientSocket, msg) < 0) {
            qDebug() << "Unable to process command: " << msg;
        }
        return;
    }

    emit newMessage(msg);
}

int Backend::checkForCommand(QString msg)
{
    QString commands = "("
                       "login|"
                       "register|"
                       "get_groups|"
                       "get_messages|"
                       "new_message"
                       ")";
    QString rx = "SRV\\|";
    rx.append(commands);
    rx.append("\\|([^\\|]*\\|)*[^\\|]*");
    QRegExp regex(rx);
    QRegExpValidator v(regex, nullptr);
    int pos = 0;

    return v.validate(msg, pos) == QValidator::Acceptable;
}

int Backend::processCommand(QTcpSocket *clientSocket, QString command)
{
    QStringList stringList = command.split("|");
    QStringList::Iterator iter = stringList.begin();
    iter++;

    qDebug() << "Command: " << *iter;
    if (*iter == "login") {
        iter++;
        QString username = *iter;
        iter++;
        QString password = *iter;

        int user_id = DbManager::checkCredentials(username, password);

        if (user_id >= 0)
            this->userIds[clientSocket] = user_id;

        // Send message containing the user id
        QString reply = "SRV|login|";
        reply.append(QString::number(user_id));
        this->server->sendToClient(clientSocket, reply);

        return 1;
    }
    if (*iter == "register") {
        iter++;
        QString username = *iter;
        iter++;
        QString password = *iter;
        iter++;
        QString email = *iter;

        int user_id = DbManager::addUser(username, password, email);

        if (user_id >= 0)
            this->userIds[clientSocket] = user_id;

        // Send message containing the user id
        QString reply = "SRV|register|";
        reply.append(QString::number(user_id));
        this->server->sendToClient(clientSocket, reply);

        return 1;
    }
    else if (*iter == "get_groups") {
        QList<QPair<QString,QString>> groupsList = DbManager::getUserGroups(this->userIds[clientSocket]);

        QString reply = "SRV|groups|";
        for (const auto &group : groupsList) {
            QString id = group.first;
            QString name = group.second;
            reply.append(id);
            reply.append(",");
            reply.append(name);
            reply.append("|");
        }

        this->server->sendToClient(clientSocket, reply);
        return 1;
    }
    else if (*iter == "get_messages") {
        iter++;
        QString groupId = *iter;
        QList<QMap<QString,QString>> messages = DbManager::selectMessagesInGroup(groupId.toUInt());

        for (const auto &message : messages) {
            QString reply = "SRV|message|";
            reply.append(message["user_id"]);
            reply.append(",");
            reply.append(groupId);
            reply.append(",");
            reply.append(message["content"]);
            reply.append(",");
            reply.append(message["creation_time"]);

            this->server->sendToClient(clientSocket, reply);
        }

        return 1;
    }
    else if (*iter == "new_message") {
        iter++;
        unsigned int groupId = (*iter).toUInt();
        iter++;
        QString content = *iter;

        int messageId = DbManager::postMessageByUser(this->userIds[clientSocket], groupId, content);
        if (messageId < 0) {
            QString reply = "SRV|message|-1|Could not add message: ";
            reply.append(content);
            this->server->sendToClient(clientSocket, reply);

            return 1;
        }
        QMap<QString,QString> message = DbManager::selectMessage(static_cast<unsigned int>(messageId));

        QString reply = "SRV|message|";
        reply.append(message["user_id"]);
        reply.append(",");
        reply.append(message["group_id"]);
        reply.append(",");
        reply.append(message["content"]);
        reply.append(",");
        reply.append(message["creation_time"]);

        // TODO: only send to users that are part of the group
        for (const auto client : this->userIds.keys()) {
            this->server->sendToClient(client, reply);
        }

        return 1;
    }
    else {
        qDebug() << "Unknown command";
    }

    return -1;
}
