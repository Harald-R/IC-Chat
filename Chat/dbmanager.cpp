#include "dbmanager.h"

#include <QSqlQuery>
#include <QSqlError>
#include <QRegularExpression>
#include <QDateTime>
#include <QDebug>

#include <iostream>

DbManager::DbManager()
{
    const QString hostname = "localhost";
    const QString databaseName = "chat";
    const QString username = "root";
    const QString password = "";

    this->db = QSqlDatabase::addDatabase("QMYSQL");
    this->db.setHostName(hostname);
    this->db.setDatabaseName(databaseName);
    this->db.setUserName(username);
    this->db.setPassword(password);
    if(!this->db.open()) {
        qDebug() << "Error opening database";
        exit(1);
    }
}

DbManager::~DbManager()
{
    if (this->db.isOpen()) {
        this->db.close();
    }
}

bool DbManager::isOpen() const
{
    return this->db.isOpen();
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
    query.prepare("DELETE FROM users WHERE uid=:user_id");
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
        qDebug() << "Failed adding user: empty parameter";
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

bool DbManager::userExists(const QString& username) const
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

void DbManager::printAllUsers() const
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

int DbManager::addMessage(const unsigned int user_id, const QString &content, const QString &creation_time)
{
    if (content.isEmpty() || creation_time.isEmpty()) {
        qDebug() << "Failed adding message: empty parameter";
        return -1;
    }

    QSqlQuery query;
    query.prepare("INSERT INTO messages (user_id, content, creation_time) VALUES (:user_id, :content, :creation_time)");
    query.bindValue(":user_id", user_id);
    query.bindValue(":content", content);
    query.bindValue(":creation_time", creation_time);

    if (!query.exec()) {
        qDebug() << "Failed adding message: " << query.lastError();
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

    int message_id = addMessage(user_id, content, creation_time);
    if (message_id < 0) {
        return message_id;
    }

    QSqlQuery query;
    query.prepare("INSERT INTO group_messages (group_id, message_id) VALUES (:group_id, :message_id)");
    query.bindValue(":group_id", group_id);
    query.bindValue(":message_id", message_id);

    if (!query.exec()) {
        qDebug() << "Failed posting message to group: " << query.lastError();
        return -1;
    }

    return message_id;
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

