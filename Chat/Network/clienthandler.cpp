#include "clienthandler.h"
#include <QRegExpValidator>

ClientHandler::ClientHandler(GroupsModel *groupsModel, ConversationModel *conversationModel, QObject *parent)
    : QObject(parent)
{
    groupsModel_ = groupsModel;
    conversationModel_ = conversationModel;

    client = new Client("localhost", 6547);
    //setStatus(client->get_status());

    connect(client, &Client::hasReadSome, this, &ClientHandler::receivedSomething);
    connect(client, &Client::statusChanged, this, &ClientHandler::setStatus);
    // TODO: change this connection to the new syntax
    connect(client->tcpSocket, SIGNAL(error(QAbstractSocket::SocketError)),
            this, SLOT(gotError(QAbstractSocket::SocketError)));
}

bool ClientHandler::getStatus()
{
    return client->getStatus();
}

void ClientHandler::requestUserGroups()
{
    sendMessage("SRV|get_groups|");
}

void ClientHandler::requestMessages(unsigned int group_id)
{
    QString msg = "SRV|get_messages|";
    msg.append(group_id);
    sendMessage(msg);
}

void ClientHandler::clearMessages()
{
    conversationModel_->clear();
}

void ClientHandler::setStatus(bool newStatus)
{
//    qDebug() << "New status is:" << newStatus;
    if (newStatus)
        { emit statusChanged("CONNECTED"); }
    else
        { emit statusChanged("DISCONNECTED"); }
}

void ClientHandler::receivedSomething(QString msg)
{
    if (checkForCommand(msg)) {
        if (!processCommand(msg)) {
            qDebug() << "Unable to process command: " << msg;
        }
        return;
    }
    emit receivedMessage(msg);
}

int ClientHandler::checkForCommand(QString msg)
{
    QRegExp regex("SRV\\|(groups|message)\\|([^\\|]*\\|)*[^\\|]*");
    QRegExpValidator v(regex, nullptr);
    int pos = 0;

    return v.validate(msg, pos) == QValidator::Acceptable;
}

int ClientHandler::processCommand(QString command)
{
    QStringList stringList = command.split("|");
    QStringList::Iterator iter = stringList.begin();
    iter++;

    if (*iter == "groups") {
        // Command that contains a comma-separated list of groups the user belogns to
        iter++;
        QList<QPair<QString,QString>> userGroups = groupsModel_->getUserGroups();
        userGroups.clear();

        while(!(*iter).isEmpty()) {
            QString str = *iter;
            QStringList strSplit = str.split(",");

            QPair<QString,QString> group;
            group.first = strSplit.first();
            group.second = strSplit.last();
            userGroups.append(group);

            iter++;
        }
        groupsModel_->replaceUserGroups(userGroups);
        return 1;
    }
    else if (*iter == "message") {
        // Command that contains a message received in a group
        // TODO: include group info?
        iter++;
        qDebug() << "Received message: " << command;
        QMap<QString,QString> message;

        QString str = *iter;
        QStringList strSplit = str.split(",");

        message["author"] = strSplit[0];
        message["content"] = strSplit[1];
        message["date"] = strSplit[2]; // TODO: concat date that contains : properly

        conversationModel_->insert(message);

        return 1;
    }

    return 0;
}

void ClientHandler::gotError(QAbstractSocket::SocketError err)
{
    QString strError = "unknown";
    switch (err)
    {
        case 0:
            strError = "Connection was refused";
            break;
        case 1:
            strError = "Remote host closed the connection";
            break;
        case 2:
            strError = "Host address was not found";
            break;
        case 5:
            strError = "Connection timed out";
            break;
        default:
            strError = "Unknown error";
    }
    qDebug() << "gotError(): " << strError.toUtf8().constData();

    emit receivedError(strError);
}

void ClientHandler::connectToServer()
{
    client->connect2host();
}

void ClientHandler::disconnectFromServer()
{
    client->closeConnection();
}

void ClientHandler::sendMessage(QString msg)
{
    QByteArray arrBlock;
    QDataStream out(&arrBlock, QIODevice::WriteOnly);
    //out.setVersion(QDataStream::Qt_5_10);
    out << quint16(0) << msg;

    out.device()->seek(0);
    out << quint16(arrBlock.size() - sizeof(quint16));

    client->tcpSocket->write(arrBlock);
}
