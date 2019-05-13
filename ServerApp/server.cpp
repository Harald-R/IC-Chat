#include "server.h"

Server::Server() : QObject(), m_nNextBlockSize(0)
{
    tcpServer = new QTcpServer();
}

QList<QSslSocket *> Server::getClients()
{
    return clients;
}

void Server::newConnection()
{
    qDebug() << "newConnection";
    QSslSocket *clientSocket = new QSslSocket;

    if (!clientSocket->setSocketDescriptor(tcpServer->socketDescriptor())) {
        delete clientSocket;
        qDebug() << "encryption fault";
        return;
    }

    clientSocket->setPrivateKey(":/server.key", QSsl::Rsa);
    clientSocket->setLocalCertificate(":/server.crt");

    connect(clientSocket, SIGNAL(sslErrors(QList<QSslError>)), this, SLOT(sslError(QList<QSslError>)));
    connect(clientSocket, &QSslSocket::encrypted, this, &Server::connectionEncrypted);
    connect(clientSocket, &QSslSocket::disconnected, clientSocket, &QSslSocket::deleteLater);
    connect(clientSocket, &QSslSocket::readyRead, this, &Server::readClient);
    connect(clientSocket, &QSslSocket::disconnected, this, &Server::gotDisconnection);

    clientSocket->startServerEncryption();

    clients << clientSocket;

    sendToClient(clientSocket, "Reply: connection established");
}

void Server::readClient()
{
    qDebug() << "readClient";
    QSslSocket *clientSocket = static_cast<QSslSocket*>(sender());
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
    qDebug() << "gotDisconnection";
    QSslSocket *clientSocket = static_cast<QSslSocket*>(sender());
    clients.removeAt(clients.indexOf(clientSocket));
    emit clientDisconnected(clientSocket);
}

void Server::connectionEncrypted()
{
    qDebug() << "connectionEncrypted";
}

void Server::sslError(QList<QSslError> errors)
{
    qDebug() << "sslError";
}

qint64 Server::sendToClient(QSslSocket *socket, const QString &str)
{
    qDebug() << "sendToClient";
    QByteArray arrBlock;
    QDataStream out(&arrBlock, QIODevice::WriteOnly);
    //out.setVersion(QDataStream::Qt_5_10);
    //out << quint16(0) << QTime::currentTime() << str;
    out << quint16(0) << str;

    out.device()->seek(0);
    out << quint16(arrBlock.size() - sizeof(quint16));

    return socket->write(arrBlock);
}
