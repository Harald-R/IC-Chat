#include "backend.h"
#include "server.h"

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

void Backend::gotNewMesssage(QString msg)
{
    emit newMessage(msg);
}
