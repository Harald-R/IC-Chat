#include "conversationmodel.h"
#include <QDebug>

ConversationModel::ConversationModel(QObject *parent) :
    QAbstractListModel(parent)
{
}

int ConversationModel::rowCount(const QModelIndex &parent) const
{
    if(parent.isValid())
        return 0;
    return messages_.size();
}

QVariant ConversationModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid() || index.row() < 0 || index.row() >= rowCount())
        return QVariant();

    const Message &message = messages_.at(index.row());
    if (role == AuthorRole) return message.author;
    if (role == ContentRole) return message.content;
    if (role == DateRole) return message.date;

    return QVariant();
}

QHash<int, QByteArray> ConversationModel::roleNames() const
{
    QHash<int, QByteArray> roles;
    roles[AuthorRole] = "author";
    roles[ContentRole] = "content";
    roles[DateRole] = "date";
    return roles;
}

void ConversationModel::insert(QMap<QString,QString> message) {
    // Extract message data
    Message m;
    m.author  = message["author"];
    m.content = message["content"];
    m.date    = message["date"];

    // Insert into the appropiate place in vector, sorted by date chronologically
    int i = rowCount();
    while (i > 0 && messages_[i-1].date < m.date) --i;

    beginInsertRows(QModelIndex(), i, i);
    messages_.insert(i, m);
    endInsertRows();
}

void ConversationModel::clear()
{
    beginRemoveRows(QModelIndex(), 0, rowCount());
    messages_.clear();
    endRemoveRows();
}

QString ConversationModel::groupId() const
{
    return groupId_;
}

QString ConversationModel::myUserId() const
{
    return myUserId_;
}

void ConversationModel::setGroupId(QString groupId)
{
    if (groupId_ == groupId)
        return;

    groupId_ = groupId;
    emit groupIdChanged(groupId_);
}

void ConversationModel::setmyUserId(QString my_user_id)
{
    if (myUserId_ == my_user_id)
        return;

    myUserId_ = my_user_id;
    emit myUserIdChanged(myUserId_);
}

