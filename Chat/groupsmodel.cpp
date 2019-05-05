#include "groupsmodel.h"
#include <QDebug>

GroupsModel::GroupsModel(QObject *parent) :
    QAbstractListModel(parent)
{
}

int GroupsModel::rowCount(const QModelIndex &parent) const
{
    if(parent.isValid())
        return 0;
    return userGroups_.size();
}

//bool GroupsModel::setData(const QModelIndex &index, const QVariant &value, int role)
//{
//    if (!hasIndex(index.row(), index.column(), index.parent()) || !value.isValid())
//        return false;

//    QPair<QString,QString> &group = userGroups_[index.row()];
//    if (role == IdRole) group.first = value.toString();
//    else if (role == NameRole) group.second = value.toString();
//    else return false;

//    emit dataChanged(index, index, { role } );

//    return true;
//}

QVariant GroupsModel::data(const QModelIndex &index, int role) const
{
    qDebug() << "data()";
    if (!index.isValid() || index.row() < 0 || index.row() >= rowCount())
        return QVariant();

    const QPair<QString,QString> &group = userGroups_.at(index.row());
    if (role == IdRole) return group.first;
    if (role == NameRole) return group.second;

    return QVariant();
}

QHash<int, QByteArray> GroupsModel::roleNames() const
{
    QHash<int, QByteArray> roles;
    roles[IdRole] = "id";
    roles[NameRole] = "name";
    return roles;
}

void GroupsModel::replaceUserGroups(QList<QPair<QString, QString>> userGroups)
{
    userGroups_ = userGroups;
//    const QModelIndex idx = index(0);
//    emit dataChanged(idx, idx);
    emit layoutChanged();
}

QList<QPair<QString, QString>> GroupsModel::getUserGroups()
{
    return userGroups_;
}

