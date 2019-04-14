#include "conversationmodel.h"
#include "dbmanager.h"

#include <QSqlRecord>

static const char *conversationsTableName = "messages";

const char* ConversationModel::COLUMN_NAMES[] = {
    "user_id",
    "group_id",
    "content",
    "creation_time",
    nullptr
};

ConversationModel::ConversationModel(QObject *parent)
    : QSqlTableModel(parent)
{
    setTable(conversationsTableName);
    setSort(4, Qt::DescendingOrder);
    setEditStrategy(QSqlTableModel::OnManualSubmit);
}

QVariant ConversationModel::data(const QModelIndex &index, int role) const
{
    if (role < Qt::UserRole)
        return QSqlTableModel::data(index, role);

    const QSqlRecord sqlRecord = record(index.row());
    return sqlRecord.value(role - Qt::UserRole);
}

QHash<int, QByteArray> ConversationModel::roleNames() const
{
    QHash<int, QByteArray> roles;
    int i = 0;
    while(COLUMN_NAMES[i] != nullptr) {
       roles.insert(Qt::UserRole + i + 1, COLUMN_NAMES[i]);
       ++i;
    }
    return roles;
}

QString ConversationModel::userId() const
{
    return userId_;
}

void ConversationModel::setUserId(const QString &userId)
{
    if (userId == userId_)
        return;

    userId_ = userId;

    emit userIdChanged();
}

QString ConversationModel::groupId() const
{
    return groupId_;
}

void ConversationModel::setGroupId(const QString &groupId)
{
    if (groupId == groupId_)
        return;

    groupId_ = groupId;

    const QString filterString = QString::fromLatin1("group_id = '%1'").arg(groupId_);
    setFilter(filterString);
    select();

    emit groupIdChanged();
}

void ConversationModel::sendMessage(const QString &message)
{
    DbManager::postMessageByUser(userId_.toUInt(), groupId_.toUInt(), message);
    select();
}
