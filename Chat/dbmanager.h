#ifndef DBMANAGER_H
#define DBMANAGER_H

#include <QtSql/QSqlDatabase>
#include <QPair>

class DbManager
{
public:
    /**
     * @brief Constructor
     *
     * Sets up connection with database and opens it
     */
    DbManager();

    /**
     * @brief Destructor
     *
     * Close the db connection
     */
    ~DbManager();

    /**
     * @brief Checks if the connection to the database is open
     * @return true - database is open
     */
    bool isOpen() const;

    /**
     * @brief Add user to database
     * @param username - username of user to add
     * @param password - password of user to add
     * @param email - email of user to add
     * @return int - user_id of new user; negative in case of error
     */
    int addUser(const QString &username, const QString &password, const QString &email);

    /**
     * @brief Remove a user from the database using their id
     * @param user_id - id of user to remove
     * @return true - user removed successfully
     */
    bool removeUser(const unsigned int user_id);

    /**
     * @brief Remove a user from the database using their username
     * @param username - username of user to remove
     * @return true - user removed successfully
     */
    bool removeUser(const QString &username);

    /**
     * @brief Check if the user with the given exists in database
     * @param username - username of user to perform check for
     * @return true - user exists
     */
    bool userExists(const QString& username) const;

    /**
     * @brief Print usernames of all users in database
     */
    void printAllUsers() const;

    /**
     * @brief Add group to database
     * @param name - name of group to add
     * @return int - group_id of new group; negative in case of error
     */
    int addGroup(const QString &name);

    /**
     * @brief Remove a group from the database using its id
     * @param group_id - id of group to remove
     * @return true - group removed successfully
     */
    bool removeGroup(const unsigned int group_id);

    /**
     * @brief Rename group using its id
     * @param group_id - id of the group
     * @param new_name - new name for the group
     * @return true - group renamed successfully
     */
    bool renameGroup(const unsigned int group_id, const QString &name);

    /**
     * @brief Add user as a member to a group
     * @param user_id - id of the user to add to group
     * @param group_id - id of the group to add the user to
     * @return true - user added successfully
     */
    bool addUserToGroup(const unsigned int user_id, const unsigned int group_id);

    /**
     * @brief Remove user from group
     * @param user_id - id of the user to remove from the group
     * @param group_id - id of the group
     * @return true - user removed successfully
     */
    bool removeUserFromGroup(const unsigned int user_id, const unsigned int group_id);

    /**
     * @brief Add message to database
     * @param user_id - the id of the message's author
     * @param content - the content of the message
     * @param creation_time - the timestamp of its creation
     * @return int - message_id of new message; negative in case of error
     */
    int addMessage(const unsigned int user_id, const QString &content, const QString &creation_time);

    /**
     * @brief Remove a message from the database using its id
     * @param message_id - id of message to remove
     * @return true - message removed successfully
     */
    bool removeMessage(const unsigned int message_id);

    /**
     * @brief Post message by user
     * @param user_id - the id of the message's author
     * @param group_id - the id of the group in which to post message
     * @param content - the content of the message
     * @param (optional) creation_time - the timestamp of its creation; default, current time
     * @return int - message_id of new message; negative in case of error
     */
    int postMessageByUser(const unsigned int user_id, const unsigned int group_id, const QString &content, QString creation_time = nullptr);

    // TODO: determine return type
    void selectMessagesInGroup(const unsigned int group_id);

private:
    QSqlDatabase db;

    bool checkEmailFormat(const QString &email);
    int getLastInsertId(const QSqlQuery &query);
};

#endif // DBMANAGER_H

