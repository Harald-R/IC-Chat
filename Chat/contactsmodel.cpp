#include "contactsmodel.h"

const char* ContactsModel::COLUMN_NAMES[] = {
    "group_id",
    "name",
    nullptr
};

const char* ContactsModel::SQL_SELECT =
    "SELECT * FROM groups";

ContactsModel::ContactsModel(QObject *parent)
    : QSqlQueryModel(parent)
{
    setQuery(SQL_SELECT);
}

QVariant ContactsModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();

    QVariant value;
    if (role < Qt::UserRole) {
        value = QSqlQueryModel::data(index, role);
    } else {
        int columnIdx = role - Qt::UserRole - 1;
        QModelIndex modelIndex = this->index(index.row(), columnIdx);
        value = QSqlQueryModel::data(modelIndex, Qt::DisplayRole);
    }

    return value;
}

QHash<int, QByteArray> ContactsModel::roleNames() const
{
    QHash<int, QByteArray> roles;
    int i = 0;
    while(COLUMN_NAMES[i] != nullptr) {
       roles.insert(Qt::UserRole + i + 1, COLUMN_NAMES[i]);
       ++i;
    }
    return roles;
}
