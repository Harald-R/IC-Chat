#ifndef SERVER_H
#define SERVER_H

#include <QTcpServer>
#include <QSslSocket>
#include <QDataStream>
#include <QList>

class Server : public QObject
{
    Q_OBJECT

public:
    Server();
    QTcpServer *tcpServer;
    QList<QSslSocket *> getClients();

public slots:
    virtual void newConnection();
    void readClient();
    void gotDisconnection();
    void connectionEncrypted();
    void sslError(QList<QSslError> errors);
    qint64 sendToClient(QSslSocket *socket, const QString &str);

signals:
    void gotNewMesssage(QSslSocket *clientSocket, QString msg);
    void clientDisconnected(QSslSocket *clientSocket);

private:
    quint16 m_nNextBlockSize;
    QList<QSslSocket *> clients;
};

#endif // SERVER_H
