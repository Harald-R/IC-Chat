#include "client.h"

Client::Client(const QString hostAddress, int portNumber) : QObject(), m_nNextBlockSize(0)
{
    status = false;
    serverSocket = new QSslSocket();

    host = hostAddress;
    port = portNumber;

    timeoutTimer = new QTimer();
    timeoutTimer->setSingleShot(true);
    connect(timeoutTimer, &QTimer::timeout, this, &Client::connectionTimeout);

    connect(serverSocket, &QSslSocket::disconnected, this, &Client::closeConnection);
}

void Client::connectToHost()
{
    qDebug() << "connectToHost";
    timeoutTimer->start(3000);

    serverSocket->ignoreSslErrors();
    connect(serverSocket, SIGNAL(sslErrors(QList<QSslError>)), this, SLOT(sslError(QList<QSslError>)));

    serverSocket->connectToHostEncrypted(host, port);
    connect(serverSocket, &QSslSocket::connected, this, &Client::connected);
    connect(serverSocket, &QSslSocket::readyRead, this, &Client::readyRead);
}

void Client::connectionTimeout()
{
    qDebug() << "connectionTimeout";
    qDebug() << serverSocket->state();
    if(serverSocket->state() == QAbstractSocket::ConnectingState)
    {
        serverSocket->abort();
        emit serverSocket->error(QAbstractSocket::SocketTimeoutError);
    }
}

void Client::sslError(QList<QSslError> errors)
{
    qDebug() << "sslError";
}

void Client::connected()
{
    qDebug() << "connected";
    status = true;
    emit statusChanged(status);
}

bool Client::getStatus()
{
    return status;
}

void Client::readyRead()
{
    qDebug() << "readyRead";
    QDataStream in(serverSocket);
    //in.setVersion(QDataStream::Qt_5_10);
    for (;;)
    {
        if (!m_nNextBlockSize)
        {
            if (serverSocket->bytesAvailable() < sizeof(quint16)) { break; }
            in >> m_nNextBlockSize;
        }

        if (serverSocket->bytesAvailable() < m_nNextBlockSize) { break; }

        QString str; in >> str;

        if (str == "0")
        {
            str = "Connection closed";
            closeConnection();
        }

        emit hasReadSome(str);
        m_nNextBlockSize = 0;
    }
}

//void Client::gotDisconnection()
//{
//    status = false;
//    emit statusChanged(status);
//}

void Client::closeConnection()
{
    qDebug() << "closeConnection";
    timeoutTimer->stop();

    //qDebug() << serverSocket->state();
    disconnect(serverSocket, &QSslSocket::connected, nullptr, nullptr);
    disconnect(serverSocket, &QSslSocket::readyRead, nullptr, nullptr);

    bool shouldEmit = false;
    switch (serverSocket->state())
    {
        case 0:
            serverSocket->disconnectFromHost();
            shouldEmit = true;
            break;
        case 2:
            serverSocket->abort();
            shouldEmit = true;
            break;
        default:
            serverSocket->abort();
    }

    if (shouldEmit)
    {
        status = false;
        emit statusChanged(status);
    }
}
