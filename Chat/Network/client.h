#ifndef CLIENT_H
#define CLIENT_H

#include <QString>
#include <QSslSocket>
#include <QDataStream>
#include <QTimer>

class Client : public QObject
{
    Q_OBJECT

public:
    Client(const QString host, int port);

    QSslSocket *serverSocket;
    bool getStatus();

public slots:
    void closeConnection();
    void connectToHost();

signals:
    void statusChanged(bool);
    void hasReadSome(QString msg);

private slots:
    void readyRead();
    void connected();
    void connectionTimeout();
    void sslError(QList<QSslError> errors);

private:
    QString host;
    int port;
    bool status;
    quint16 m_nNextBlockSize;
    QTimer *timeoutTimer;
};

#endif // CLIENT_H
