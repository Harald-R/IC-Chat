#ifndef SERVER_H
#define SERVER_H

#include <QTcpServer>
#include <QTcpSocket>
#include <QDataStream>
#include <QList>

class Server : public QObject
{
    Q_OBJECT

public:
    Server();
    QTcpServer *tcpServer;
    QList<QTcpSocket *> getClients();

public slots:
    virtual void newConnection();
    void readClient();
    void gotDisconnection();
    qint64 sendToClient(QTcpSocket *socket, const QString &str);

signals:
    void gotNewMesssage(QTcpSocket *clientSocket, QString msg);
    void clientDisconnected(QTcpSocket *clientSocket);

private:
    quint16 m_nNextBlockSize;
    QList<QTcpSocket*> clients;
};

#endif // SERVER_H
