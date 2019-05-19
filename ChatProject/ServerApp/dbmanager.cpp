#include "dbmanager.h"

#include <QSqlQuery>
#include <QSqlError>
#include <QRegularExpression>
#include <QDateTime>
#include <QDebug>

#include <iostream>

void DbManager::connect()
{
    const QString hostname = "localhost";
    const QString databaseName = "chat";
    const QString username = "root";
    const QString password = "";

    QSqlDatabase db = QSqlDatabase::addDatabase("QMYSQL");
    db.setHostName(hostname);
    db.setDatabaseName(databaseName);
    db.setUserName(username);
    db.setPassword(password);
    if(!db.open()) {
        qDebug() << "Error opening database";
        exit(1);
    }
}

void DbManager::closeConnection()
{
    QSqlDatabase db = QSqlDatabase::database();
    if (db.isOpen()) {
        db.close();
    }
}

bool DbManager::isOpen()
{
    return QSqlDatabase::database().isOpen();
}

int DbManager::checkCredentials(const QString &username, const QString &password)
{
    if (username.isEmpty() || password.isEmpty()) {
        qDebug() << "Failed checking credentials: empty parameter";
        return -1;
    }

    QSqlQuery query;
    query.prepare("SELECT * FROM users WHERE username=:username AND password=:password");
    query.bindValue(":username", username);
    query.bindValue(":password", password);

    if (!query.exec()) {
        qDebug() << "Failed checking credentials: " << query.lastError();
        return -1;
    }

    if (query.next()) {
        return query.value("user_id").toInt();
    }

    return -1;
}

int DbManager::addUser(const QString &username, const QString &password, const QString &email)
{
    if (username.isEmpty() || password.isEmpty() || email.isEmpty()) {
        qDebug() << "Failed adding user: empty parameter";
        return -1;
    }

    if (!checkEmailFormat(email)) {
        qDebug() << "Failed adding user: invalid email";
        return -1;
    }

    QSqlQuery query;
    query.prepare("INSERT INTO users (username, password, email) VALUES (:username, :password, :email)");
    query.bindValue(":username", username);
    query.bindValue(":password", password);
    query.bindValue(":email", email);

    if (!query.exec()) {
        qDebug() << "Failed adding user: " << query.lastError();
        return -1;
    }

    return getLastInsertId(query);
}

bool DbManager::removeUser(const unsigned int user_id)
{
    QSqlQuery query;
    query.prepare("DELETE FROM users WHERE user_id=:user_id");
    query.bindValue(":user_id", user_id);

    if (!query.exec()) {
        qDebug() << "Failed removing user: " << query.lastError();
        return false;
    }

    return true;
}

bool DbManager::removeUser(const QString &username)
{
    if (username.isEmpty()) {
        qDebug() << "Failed removing user: empty parameter";
        return false;
    }

    QSqlQuery query;
    query.prepare("DELETE FROM users WHERE username=:username");
    query.bindValue(":username", username);

    if (!query.exec()) {
        qDebug() << "Failed removing user: " << query.lastError();
        return false;
    }

    return true;
}

bool DbManager::userExists(const QString& username)
{
    if (username.isEmpty()) {
        qDebug() << "Failed checking for user: empty parameter";
        return false;
    }

    QSqlQuery query;
    query.prepare("SELECT * FROM users WHERE username=:username");
    query.bindValue(":username", username);

    if (!query.exec()) {
        qDebug() << "Failed checking for user: " << query.lastError();
        return false;
    }

    return query.next();
}

void DbManager::printAllUsers()
{
    QSqlQuery query;
    query.prepare("SELECT username FROM users");

    if (!query.exec()) {
        qDebug() << "Failed checking for user: " << query.lastError();
    }

    while(query.next()) {
        std::cout << "Username: " << query.value("username").toString().toUtf8().constData() << std::endl;
    }
}

QList<QPair<QString,QString>> DbManager::getUserGroups(const unsigned int user_id)
{
    QList<QPair<QString,QString>> groupsList;

    QSqlQuery query;
    query.prepare("SELECT g.* FROM groups AS g INNER JOIN group_users AS gu ON g.group_id = gu.group_id AND gu.user_id = :user_id");
    query.bindValue(":user_id", user_id);

    if (!query.exec()) {
        qDebug() << "Failed checking for user: " << query.lastError();
        return groupsList;
    }

    while(query.next()) {
        QPair<QString, QString> group;
        group.first  = query.value("group_id").toString();
        group.second = query.value("name").toString();
        groupsList.append(group);

        qDebug() << "Group_id: " << query.value("group_id").toString().toUtf8().constData() <<
                    ", name: " << query.value("name").toString().toUtf8().constData();
    }
    return groupsList;
}

int DbManager::addGroup(const QString &name)
{
    if (name.isEmpty()) {
        qDebug() << "Failed adding group: empty parameter";
        return -1;
    }

    QSqlQuery query;
    query.prepare("INSERT INTO groups (name) VALUES (:name)");
    query.bindValue(":name", name);

    if (!query.exec()) {
        qDebug() << "Failed adding group: " << query.lastError();
        return -1;
    }

    return getLastInsertId(query);
}

bool DbManager::removeGroup(const unsigned int group_id)
{
    QSqlQuery query;
    query.prepare("DELETE FROM groups WHERE group_id=:group_id");
    query.bindValue(":group_id", group_id);

    if (!query.exec()) {
        qDebug() << "Failed removing group: " << query.lastError();
        return false;
    }

    return true;
}

bool DbManager::renameGroup(const unsigned int group_id, const QString &name)
{
    if (name.isEmpty()) {
        qDebug() << "Failed renaming group: empty parameter";
        return false;
    }

    QSqlQuery query;
    query.prepare("groups  SET name=:name WHERE group_id=:group_id");
    query.bindValue(":name", name);
    query.bindValue(":group_id", group_id);

    if (!query.exec()) {
        qDebug() << "Failed renaming group: " << query.lastError();
        return false;
    }

    return true;
}

bool DbManager::addUserToGroup(const unsigned int user_id, const unsigned int group_id)
{
    QSqlQuery query;
    query.prepare("INSERT INTO group_users (group_id, user_id) VALUES (:group_id, :user_id)");
    query.bindValue(":group_id", group_id);
    query.bindValue(":user_id", user_id);

    if (!query.exec()) {
        qDebug() << "Failed adding user to group: " << query.lastError();
        return false;
    }

    return true;
}

bool DbManager::removeUserFromGroup(const unsigned int user_id, const unsigned int group_id)
{
    QSqlQuery query;
    query.prepare("DELETE FROM group_users WHERE group_id=:group_id AND user_id=:user_id");
    query.bindValue(":group_id", group_id);
    query.bindValue(":user_id", user_id);

    if (!query.exec()) {
        qDebug() << "Failed renaming group: " << query.lastError();
        return false;
    }

    return true;
}

int DbManager::addMessage(const unsigned int user_id, const unsigned int group_id, const QString &content, const QString &creation_time)
{
    if (content.isEmpty() || creation_time.isEmpty()) {
        QDebug(QtCriticalMsg) << "Failed adding message: empty parameter";
        return -1;
    }

    QSqlQuery query;
    query.prepare("INSERT INTO messages (user_id, group_id, content, creation_time) VALUES (:user_id, :group_id, :content, :creation_time)");
    query.bindValue(":user_id", user_id);
    query.bindValue(":group_id", group_id);
    query.bindValue(":content", content);
    query.bindValue(":creation_time", creation_time);

    if (!query.exec()) {
        QDebug(QtCriticalMsg) << "Failed adding message: " << query.lastError();
        return -1;
    }

    return getLastInsertId(query);
}

bool DbManager::removeMessage(const unsigned int message_id)
{
    QSqlQuery query;
    query.prepare("DELETE FROM messages WHERE message_id=:message_id");
    query.bindValue(":message_id", message_id);

    if (!query.exec()) {
        qDebug() << "Failed removing message: " << query.lastError();
        return false;
    }

    return true;
}

int DbManager::postMessageByUser(const unsigned int user_id, const unsigned int group_id, const QString &content, QString creation_time)
{
    if (content.isEmpty() || (creation_time != nullptr && creation_time.isEmpty())) {
        qDebug() << "Failed posting message: empty parameter";
        return -1;
    }

    if (creation_time == nullptr) {
        creation_time = QDateTime::currentDateTimeUtc().toString("yyyy-MM-dd hh:mm:ss");
    }

    int message_id = addMessage(user_id, group_id, content, creation_time);
    return message_id;
}

QMap<QString, QString> DbManager::selectMessage(const unsigned int message_id)
{
    QMap<QString, QString> message;

    QSqlQuery query;
    query.prepare("SELECT * FROM messages WHERE message_id=:message_id");
    query.bindValue(":message_id", message_id);

    if (!query.exec()) {
        qDebug() << "Failed selecting message: " << query.lastError();
        return message;
    }

    if (query.next()) {
        message.insert("user_id", query.value("user_id").toString());
        message.insert("group_id", query.value("group_id").toString());
        message.insert("content", query.value("content").toString());
        message.insert("creation_time", query.value("creation_time").toString());

        qDebug() << "user_id: " << query.value("user_id").toString().toUtf8().constData() <<
                    ", group_id: " << query.value("group_id").toString().toUtf8().constData() <<
                    ", content: " << query.value("content").toString().toUtf8().constData() <<
                    ", creation_time: " << query.value("creation_time").toString().toUtf8().constData();
    }

    return message;
}

QList<QMap<QString, QString>> DbManager::selectMessagesInGroup(const unsigned int group_id)
{
    QList<QMap<QString, QString>> messages;

    QSqlQuery query;
    query.prepare("SELECT * FROM messages WHERE group_id=:group_id");
    query.bindValue(":group_id", group_id);

    if (!query.exec()) {
        qDebug() << "Failed selecting messages: " << query.lastError();
        return messages;
    }

    qDebug() << "Messages in group " << group_id << ":";
    while (query.next()) {
        QMap<QString, QString> message;
        message.insert("user_id", query.value("user_id").toString());
        message.insert("content", query.value("content").toString());
        message.insert("creation_time", query.value("creation_time").toString());
        messages.append(message);

        qDebug() << "user_id: " << query.value("user_id").toString().toUtf8().constData() <<
                    ", content: " << query.value("content").toString().toUtf8().constData() <<
                    ", creation_time: " << query.value("creation_time").toString().toUtf8().constData();
    }

    return messages;
}

bool DbManager::checkEmailFormat(const QString &email)
{
    QRegularExpression regex("\\b[A-Z0-9._%+-]+@[A-Z0-9.-]+\\.[A-Z]{2,4}\\b",
                             QRegularExpression::CaseInsensitiveOption);
    return regex.match(email).hasMatch();
}

int DbManager::getLastInsertId(const QSqlQuery &query)
{
    int id = query.lastInsertId().toInt();
    if (id < 0) {
        qDebug() << "Failed retrieving ID of last insert: " << id;
    }

    return id;
}

