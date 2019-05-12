#include "server.h"

Server::Server() : QObject(), m_nNextBlockSize(0)
{
    tcpServer = new QTcpServer();
}

QList<QTcpSocket *> Server::getClients()
{
    return clients;
}

void Server::newConnection()
{
    QTcpSocket *clientSocket = tcpServer->nextPendingConnection();

    connect(clientSocket, &QTcpSocket::disconnected, clientSocket, &QTcpSocket::deleteLater);
    connect(clientSocket, &QTcpSocket::readyRead, this, &Server::readClient);
    connect(clientSocket, &QTcpSocket::disconnected, this, &Server::gotDisconnection);

    clients << clientSocket;

    sendToClient(clientSocket, "Reply: connection established");
}

void Server::readClient()
{
    QTcpSocket *clientSocket = static_cast<QTcpSocket*>(sender());
    QDataStream in(clientSocket);
    //in.setVersion(QDataStream::Qt_5_10);
    for (;;)
    {
        if (!m_nNextBlockSize)
        {
            if (clientSocket->bytesAvailable() < sizeof(quint16)) { break; }
            in >> m_nNextBlockSize;
        }

        if (clientSocket->bytesAvailable() < m_nNextBlockSize) { break; }
        QString str;
        in >> str;

        emit gotNewMesssage(clientSocket, str);

        m_nNextBlockSize = 0;

//        if (sendToClient(clientSocket, QString("Reply: received [%1]").arg(str)) == -1)
//        {
//            qDebug() << "Some error occured";
//        }
    }
}

void Server::gotDisconnection()
{
    QTcpSocket *clientSocket = static_cast<QTcpSocket*>(sender());
    clients.removeAt(clients.indexOf(clientSocket));
    emit clientDisconnected(clientSocket);
}

qint64 Server::sendToClient(QTcpSocket *socket, const QString &str)
{
    QByteArray arrBlock;
    QDataStream out(&arrBlock, QIODevice::WriteOnly);
    //out.setVersion(QDataStream::Qt_5_10);
    //out << quint16(0) << QTime::currentTime() << str;
    out << quint16(0) << str;

    out.device()->seek(0);
    out << quint16(arrBlock.size() - sizeof(quint16));

    return socket->write(arrBlock);
}
